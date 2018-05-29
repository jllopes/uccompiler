#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_gen.h"
#include "sym_table.h"

char* types_to_llvm(char* type){ /* Returns types as llvm */
	if(!strcmp(type, "Int") || !strcmp(type, "int")) {
		return strdup("i32");
	} else if(!strcmp(type, "Double") || !strcmp(type, "double")) {
		return strdup("double");
	} else if(!strcmp(type, "Short") || !strcmp(type, "short")) {
		return strdup("i16");
	} else if(!strcmp(type, "Char") || !strcmp(type, "char")) {
		return strdup("i8");
	} else if(!strcmp(type, "Void")) {
		return strdup("void");
	}
	/* No valid type */
	return "null";
}

void code_gen(Node *node){
	//printf("\nNode token: %s\n", node->token);
	if(!strcmp(node->token, "Program")) {
		program_gen(node);
	} else if(!strcmp(node->token, "Declaration")) {
		declaration_gen(node);
	} else if(!strcmp(node->token, "FuncDefinition")) {
		func_definition_gen(node);
	} else if(!strcmp(node->token, "ParamList")) {
		params_gen(node);
	} else if(!strcmp(node->token, "FuncBody")) {
		func_body_gen(node);
	} else if(!strcmp(node->token, "ChrLit")) {
		chrlit_gen(node);
	} else if(!strcmp(node->token, "IntLit")) {
		intlit_gen(node);
	} else if(!strcmp(node->token, "RealLit")) {
		reallit_gen(node);
	} else if(!strcmp(node->token, "Id")){
		id_gen(node);
	} else if(!strcmp(node->token, "Store")) {
		store_gen(node);
	} else if(!strcmp(node->token, "Plus")) {
		code_gen(node->child);
	} else if(!strcmp(node->token, "Minus")) {
		minus_gen(node);
	} else if(!strcmp(node->token, "Return")) {
		//return_gen(node);
	} else if(!strcmp(node->token, "Call")) {
		call_gen(node);
	} 
}

void program_gen(Node *node){
	/* Generate code for every child */
	Node *aux = node->child;
	while(aux != NULL){
		code_gen(aux);
		if(aux->brother == NULL)
			break;
		aux = aux->brother;
	}
	/* Putchar and Getchar (default functions) */
	printf("declare i32 @putchar(i32)\n");
	printf("declare i32 @getchar()\n\n");
}

void declaration_gen(Node *node){
	char *type = types_to_llvm(node->child->token);
	if(node->child->brother->brother == NULL){
		if(!strcmp(type, "double")) { /* Double has different initialize value */
			printf("@%s = common global double 0.000000e+00\n", node->child->brother->value);
		} else { /* Int, Short, Char */
			printf("@%s = common global %s 0\n", node->child->brother->value, type);
		}
	} else { /* It has value assigned */
		printf("@%s = global %s %s\n", node->child->brother->value, type, node->child->brother->brother->value);
	}
}

void local_declaration_gen(Node *node){
	char *type = types_to_llvm(node->child->token);
	char *name = node->child->brother->value;
	printf("%%%s = alloca %s\n", name, type);
	if(node->child->brother->brother != NULL){
		if(!strcmp(node->child->brother->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, type, type);
			code_gen(node->child->brother->brother);
			printf("\n");
			printf("store %s %%%d, %s* %%%s\n", type, temporary_var, type, name);
			temporary_var++;
		} else {
			printf("store %s ", type);
			code_gen(node->child->brother->brother);
			printf(", %s* %%%s\n", type, name);
		}	
	}
}

void func_definition_gen(Node *node){
	temporary_var = 1;
	char *type = types_to_llvm(node->child->token);
	char *name = node->child->brother->value; /* Value from ID */
	printf("define %s @%s", type, name);
	Node *aux = node->child->brother->brother; /* Skips until ParamList */
	params_gen(aux->child);
	printf("{\n");
	aux = aux->brother; /* Skips FuncBody */
	code_gen(aux);
	if(!strcmp(type, "void")){
		printf("ret void\n");
	} else if(!strcmp(type, "double")){
		printf("ret double 0.0\n");
	} else {
		printf("ret %s 0\n", type);
	}
	printf("}\n\n");
}

void params_gen(Node *node){ /* Receives first ParamDeclaration */
	Node *aux = node;
	printf("(");
	while(aux != NULL){ /* Goes through all Params */
		char *type = types_to_llvm(aux->child->token);
		if(!strcmp(type, "void")){
			printf(") ");
			return;
		} else {
			if(aux->brother != NULL){ /* Has more params */
				printf("%s %%%s,", type, aux->child->brother->value); /* Prints type and id */
			} else { /* Last Param */
				printf("%s %%%s) ", type, aux->child->brother->value); /* Prints type and id */
			}
		}
		if(aux->brother == NULL)
			break;
		aux = aux->brother;
	}
}

void func_body_gen(Node *node){
	Node *aux = node->child;
	while(aux != NULL){
		if(!strcmp(aux->token, "Declaration")){
			local_declaration_gen(aux);
		} else {
			code_gen(aux);
		}
		if(aux->brother == NULL)
			break;
		aux = aux->brother;
	}
	
}

void chrlit_gen(Node *node){
	if(node->value[1] == '\\'){
		if(node->value[2] == 'n'){
			char tmp = '\n';
			printf("%d", tmp);
		} else if(node->value[2] == 't'){
			char tmp = '\t';
			printf("%d", tmp);
		} else if(node->value[2] == 'r'){
			char tmp = '\r';
			printf("%d", tmp);
		} else if(node->value[2] == '\''){
			char tmp = '\'';
			printf("%d", tmp);
		} else if(node->value[2] == '\\'){
			char tmp = '\\';
			printf("%d", tmp);
		} else {
			if(node->value[3] == '\''){
				char seq[1];
				char *extra;
				sprintf(seq,"%c",node->value[2]);
				printf("%ld", strtol(seq, &extra, 8));
			} else if(node->value[4] == '\''){
				char seq[2];
				char *extra;
				sprintf(seq,"%c%c",node->value[2], node->value[3]);
				printf("%ld", strtol(seq, &extra, 8));
			} else {
				char seq[3];
				char *extra;
				sprintf(seq,"%c%c%c",node->value[2], node->value[3], node->value[4]);
				printf("%ld", strtol(seq, &extra, 8));
			}
		}
	} else {
		printf("%d", node->value[1]);
	}
}

void intlit_gen(Node *node){
	printf("%s", node->value);
}

void reallit_gen(Node *node){
	printf("%s", node->value);
}

void id_gen(Node *node){
	Symbol *aux = global->symbol;
	while(aux){
		if(!strcmp(aux->name, node->value)){
			printf("@%s", node->value);
			return;
		}
		aux = aux->next;
	}
	printf("%%%s", node->value);
}

void store_gen(Node *node){
	char *type = types_to_llvm(node->child->type);
	char *name = node->child->value;
	printf("store %s ", type);
	code_gen(node->child->brother);
	Symbol *aux = global->symbol;
	while(aux){ /* Checks if is global */
		if(!strcmp(aux->name, name)){
			printf(", %s* @%s\n", type, name);
			return;
		}
		aux = aux->next;
	}
	printf(", %s* %%%s\n", type, name);
}

void minus_gen(Node *node){
	printf("-");
	code_gen(node->child);
}

void call_gen(Node *node){
	char *name = node->child->value;
	char *type = types_to_llvm(node->child->type);
	Symbol *symbol = global->symbol;
	while(symbol != NULL){
		if(!strcmp(symbol->name, name)){
			break;
		}
		symbol = symbol->next;
	}
	int params = 0;
	int param_array[999];
	Node *aux = node->child->brother; /* First Param */
	Param *param = symbol->param;
	char *param_type, *expected_type;
	while(aux != NULL){ /* Goes through parameters to load values to temporary variables */
		param_type = types_to_llvm(aux->type);
		expected_type = types_to_llvm(param->type);
		if(strcmp(param_type, expected_type)){ /* Different types, needs to convert */
			if(!strcmp(aux->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, param_type, param_type);
				code_gen(aux);
				printf("\n");
				temporary_var++;
				convert_types(aux, expected_type);
				param_array[params] = temporary_var; /* Access on call */
				temporary_var++;
			} else {
				convert_types(aux, expected_type);
				param_array[params] = temporary_var;
				temporary_var++;
			}
		} else {
			if(!strcmp(aux->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, param_type, param_type);
				code_gen(aux);
				printf("\n");
				param_array[params] = temporary_var; /* Access on call */
				temporary_var++;
			}
		}
		param++;
		param = param->next;
		aux = aux->brother;
	}
	printf("%%%d = call %s @%s(", temporary_var, type, name);
	temporary_var++;
	aux = node->child->brother;
	param = symbol->param;
	int temp = 0;
	while(aux != NULL){
		param_type = types_to_llvm(aux->type);
		expected_type = types_to_llvm(param->type);
		if(strcmp(param_type, expected_type)){ /* Different types */
			if(aux->brother == NULL){
				printf("%s %%%d)\n", expected_type, param_array[temp]);
			} else {
				printf("%s %%%d,", expected_type, param_array[temp]);		
			}
		} else {
			if(aux->brother == NULL){
				if(!strcmp(aux->token, "Id")){
					printf("%s %%%d)\n", expected_type, param_array[temp]);
				} else {
					printf("%s ", expected_type);
					code_gen(aux);
					printf(")\n");
				}
			} else {
				if(!strcmp(aux->token, "Id")){
					printf("%s %%%d,",  expected_type, param_array[temp]);
				} else {
					printf("%s ", expected_type);
					code_gen(aux);
					printf(",");
				}
			}
		}
		temp++;
		param = param->next;
		aux = aux->brother;
	}
}

void return_gen(Node *node){
	char *type = types_to_llvm(node->child->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, type, type);
		code_gen(node->child);
		printf("\n");
	} else {
		printf("store %s ", type);
		code_gen(node->child);
		printf(", %s* %%%d\n", type, temporary_var);
	}
	printf("ret %s %%%d\n", type, temporary_var);
	temporary_var++;
}

void convert_types(Node *received, char *expected){
	if(((!strcmp(received->type, "int") || !strcmp(received->type, "short")) && !strcmp(expected, "i8")) || (!strcmp(received->type, "int") && !strcmp(expected, "i16"))){ /* Expected char - Got int, short || Expected short - Got int*/
		if(!strcmp(received->token, "Id")){
			printf("%%%d = trunc %s %%%d to %s\n", temporary_var, types_to_llvm(received->type), temporary_var-1, expected);
		} else {
			printf("%%%d = trunc %s ", temporary_var, types_to_llvm(received->type));
			code_gen(received);
			printf(" to %s\n", expected);
		}
	} else if((!strcmp(expected, "i8") || !strcmp(expected, "i16") || !strcmp(expected, "i32")) && !strcmp(received->type, "double")){ /* Expected char, short, int - Got double */
		if(!strcmp(received->token, "Id")){
			printf("%%%d = fptosi double %%%d to %s\n", temporary_var, temporary_var-1, expected);
		} else {
			printf("%%%d = fptosi double ", temporary_var);
			code_gen(received);
			printf(" to %s\n", expected);
		}
	} else {
		if(!strcmp(received->token, "Id")){
			printf("%%%d = sext %s %%%d to %s\n", temporary_var, types_to_llvm(received->type), temporary_var-1, expected);
		} else {
			printf("%%%d = sext ", temporary_var);
			code_gen(received);
			printf(" to %s\n", expected);
		}
	}
}