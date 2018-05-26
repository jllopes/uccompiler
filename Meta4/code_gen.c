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

void code_gen(Node *node, char *function){
	//printf("\nNode token: %s\n", node->token);
	if(!strcmp(node->token, "Program")) {
		program_gen(node, function);
	} else if(!strcmp(node->token, "Declaration")) {
		declaration_gen(node, function);
	} /*else if(!strcmp(node->token, "FuncDeclaration")) {
		//func_declaration_gen(node); NECESSARY?
	} */ else if(!strcmp(node->token, "FuncDefinition")) {
		func_definition_gen(node, function);
	} else if(!strcmp(node->token, "ParamList")) {
		params_gen(node, function);
	} else if(!strcmp(node->token, "FuncBody")) {
		func_body_gen(node, function);
	} else if(!strcmp(node->token, "ChrLit")) {
		chrlit_gen(node, function);
	} else if(!strcmp(node->token, "IntLit")) {
		intlit_gen(node, function);
	} else if(!strcmp(node->token, "RealLit")) {
		reallit_gen(node, function);
	} else if(!strcmp(node->token, "Store")) {
		store_gen(node, function);
	} else if(!strcmp(node->token, "Plus")) {
		code_gen(node->child, function);
	} else if(!strcmp(node->token, "Minus")) {
		minus_gen(node, function);
	} else if(!strcmp(node->token, "Return")) {
		return_gen(node, function);
	} else if(!strcmp(node->token, "Call")) {
		call_gen(node, function);
	}
}

void program_gen(Node *node, char *function){
	/* Putchar and Getchar (default functions) */
	printf("declare i32 @putchar(i32)\n");
	printf("declare i32 @getchar()\n\n");
	/* Generate code for every child */
	Node *aux = node->child;
	while(aux != NULL){
		code_gen(aux, function);
		if(aux->brother == NULL)
			break;
		aux = aux->brother;
	}
}

void declaration_gen(Node *node, char *function){
	char *type = types_to_llvm(node->child->token);
	if(node->child->brother->brother == NULL){
		if(!strcmp(type, "double")) { /* Double has different initialize value */
			printf("@%s = common global double 0.000000e+00\n\n", node->child->brother->value);
		} else { /* Int, Short, Char */
			printf("@%s = common global %s 0\n\n", node->child->brother->value, type);
		}
	} else { /* It has value assigned */
		printf("@%s = global %s %s\n\n", node->child->brother->value, type, node->child->brother->brother->value);
	}
}

void local_declaration_gen(Node *node, char *function){
	char *type = types_to_llvm(node->child->token);
	char *name = node->child->brother->value;
	printf("%%%s.%s = alloca %s\n", function, name, type);
	if(node->child->brother->brother != NULL){
		printf("store %s ", type);
		code_gen(node->child->brother->brother, function);
		printf(", %s* %%%s.%s\n", type, function, name);
	}
}

void func_definition_gen(Node *node, char *function){
	temporary_var = 1;
	char *type = types_to_llvm(node->child->token);
	char *name = node->child->brother->value; /* Value from ID */
	printf("define %s @%s", type, name);
	Node *aux = node->child->brother->brother; /* Skips until ParamList */
	params_gen(aux->child, function);
	printf("{\n");
	aux = aux->brother; /* Skips FuncBody */
	code_gen(aux, name);
	if(!strcmp(type, "void")){
		printf("ret void\n");
	}
	printf("}\n\n");
}

void params_gen(Node *node, char *function){ /* Receives first ParamDeclaration */
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

void func_body_gen(Node *node, char *function){
	Node *aux = node->child;
	while(aux != NULL){
		if(!strcmp(aux->token, "Declaration")){
			local_declaration_gen(aux, function);
		} else {
			code_gen(aux, function);
		}
		if(aux->brother == NULL)
			break;
		aux = aux->brother;
	}
	
}

void chrlit_gen(Node *node, char *function){
	printf("%d", node->value[1]);
}

void intlit_gen(Node *node, char *function){
	printf("%s", node->value);
}

void reallit_gen(Node *node, char *function){
	printf("%s", node->value);
}

void store_gen(Node *node, char *function){
	char *type = types_to_llvm(node->child->brother->type);
	char *name = node->child->value;
	printf("store %s ", type);
	code_gen(node->child->brother, function);
	printf(", %s* %%%s.%s\n", type, function, name);
}

void minus_gen(Node *node, char *function){
	printf("-");
	code_gen(node->child, function);
}

void call_gen(Node *node, char *function){
	char *name = node->child->value;
	char *type = types_to_llvm(node->child->type);
	Node *aux = node->child->brother; /* First Param */
	char *param_type;
	int temp = temporary_var;
	while(aux != NULL){
		param_type = types_to_llvm(aux->type);
		printf("%%%d = load %s, %s* %%%s.%s\n", temporary_var, param_type, param_type, function, aux->value);
		temporary_var++;
		aux = aux->brother;
	}
	printf("%%%d = call %s @%s(", temporary_var, type, name);
	temporary_var++;
	aux = node->child->brother;
	while(aux != NULL){
		param_type = types_to_llvm(aux->type);
		if(aux->brother == NULL){
			printf("%s %%%d)\n", param_type, temp);
		} else {
			printf("%s %%%d,",  param_type, temp);
		}
		temp++;
		aux = aux->brother;
	}
}

void return_gen(Node *node, char *function){
	char *name = node->child->value;
	char *type = types_to_llvm(node->child->type);
	printf("%%%d = load %s, %s* %%%s.%s\n", temporary_var, type, type, function, name);
	printf("ret %s %%%d\n", type, temporary_var);
	temporary_var++;
}