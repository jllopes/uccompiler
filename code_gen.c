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
		return_gen(node);
	} else if(!strcmp(node->token, "Call")) {
		call_gen(node);
	} else if(!strcmp(node->token, "Add")) {
		add_gen(node);
	} else if(!strcmp(node->token, "Sub")) {
		sub_gen(node);
	} else if(!strcmp(node->token, "Mul")) {
		mul_gen(node);
	} else if(!strcmp(node->token, "Div")) {
		div_gen(node);
	} else if(!strcmp(node->token, "Mod")) {
		mod_gen(node);
	} else if(!strcmp(node->token, "Or")) {
		or_gen(node);
	} else if(!strcmp(node->token, "And")) {
		and_gen(node);
	} else if(!strcmp(node->token, "BitWiseAnd")) {
		bitwiseand_gen(node);
	} else if(!strcmp(node->token, "BitWiseOr")) {
		bitwiseor_gen(node);
	} else if(!strcmp(node->token, "BitWiseXor")) {
		bitwisexor_gen(node);
	} else if(!strcmp(node->token, "Eq")) {
		eq_gen(node);
	} else if(!strcmp(node->token, "Ne")) {
		ne_gen(node);
	} else if(!strcmp(node->token, "Le")) {
		le_gen(node);
	} else if(!strcmp(node->token, "Ge")) {
		ge_gen(node);
	} else if(!strcmp(node->token, "Lt")) {
		lt_gen(node);
	} else if(!strcmp(node->token, "Gt")) {
		gt_gen(node);
	} else if(!strcmp(node->token, "Not")) {
		not_gen(node);
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
		printf("@%s = global %s ", node->child->brother->value, type);
		code_gen(node->child->brother->brother);
		printf("\n");
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
			temporary_var++;
			printf("store %s %%%d, %s* %%%s\n", type, temporary_var, type, name);
		} else if(!strcmp(node->child->brother->brother->token, "IntLit") || !strcmp(node->child->brother->brother->token, "RealLit") || !strcmp(node->child->brother->brother->token, "ChrLit")){ /* Other Terminal */
			printf("store %s ", type);
			code_gen(node->child->brother->brother);
			printf(", %s* %%%s\n", type, name);
		} else if(!strcmp(node->child->brother->brother->token, "Minus") || !strcmp(node->child->brother->brother->token, "Plus")){
			if(!strcmp(node->child->brother->brother->child->token, "IntLit") || !strcmp(node->child->brother->brother->child->token, "RealLit") || !strcmp(node->child->brother->brother->child->token, "ChrLit")){
				printf("store %s ", type);
				code_gen(node->child->brother->brother);
				printf(", %s* %%%s\n", type, name);
			} else {
				code_gen(node->child->brother->brother);
				printf("store %s %%%d, %s* %%%s\n", type, temporary_var-1, type, name);
			}
		} else { /* Expressions */
			code_gen(node->child->brother->brother);
			printf("store %s %%%d, %s* %%%s\n", type, temporary_var-1, type, name);
		}
	}
}

void func_definition_gen(Node *node){
	temporary_var = 1;
	and_cmp = 1;
	or_cmp = 1;
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
		} else if(node->value[2] == '\"'){
			char tmp = '\"';
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
	int global = is_global(name);
	if(!strcmp(node->child->brother->token, "IntLit") || !strcmp(node->child->brother->token, "RealLit") || !strcmp(node->child->brother->token, "ChrLit") || !strcmp(node->child->brother->token, "Id")){
		printf("store %s ", type);
		code_gen(node->child->brother);
		if(global){
			printf(", %s* @%s\n", type, name);
		} else {
			printf(", %s* %%%s\n", type, name);
		}
	} else if(!strcmp(node->child->brother->token, "Minus") || !strcmp(node->child->brother->token, "Plus")){
			if(!strcmp(node->child->brother->child->token, "IntLit") || !strcmp(node->child->brother->child->token, "RealLit") || !strcmp(node->child->brother->child->token, "ChrLit")){
				printf("store %s ", type);
				code_gen(node->child->brother);
				if(global) {
					printf(", %s* @%s\n", type, name);
				} else {
					printf(", %s* %%%s\n", type, name);
				}
			} else {
				code_gen(node->child->brother);
				if(global){
					printf("store %s %%%d, %s* @%s\n", type, temporary_var-1, type, name);
				} else {
					printf("store %s %%%d, %s* %%%s\n", type, temporary_var-1, type, name);
				}
			}
	} else {
		code_gen(node->child->brother);
		if(global){
			printf("store %s %%%d, %s* @%s\n", type, temporary_var-1, type, name);
		} else {
			printf("store %s %%%d, %s* %%%s\n", type, temporary_var-1, type, name);
		}
		
	}
}

void minus_gen(Node *node){
	if(!strcmp(node->child->token, "IntLit") || !strcmp(node->child->token, "RealLit") || !strcmp(node->child->token, "ChrLit")){
			printf("-");
			code_gen(node->child);
	} else if(!strcmp(node->child->token, "Id")){
		if(!strcmp(node->child->type, "double")){
			printf("%%%d = load double, double* ", temporary_var);
			code_gen(node->child);
			printf("\n");
			temporary_var++;
			printf("%%%d = fmul double -1.0, %%%d\n", temporary_var, temporary_var-1);
		} else {
			printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(node->child->type), types_to_llvm(node->child->type));
			code_gen(node->child);
			printf("\n");
			temporary_var++;
			printf("%%%d = mul %s -1, %%%d\n", temporary_var, types_to_llvm(node->child->type), temporary_var-1);
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->type, "double")){
			printf("%%%d = fmul double -1.0, %%%d\n", temporary_var, temporary_var-1);
		} else {
			printf("%%%d = mul %s -1, %%%d\n", temporary_var, types_to_llvm(node->child->type), temporary_var-1);
		}
		temporary_var++;
	}
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
				param_array[params] = temporary_var-1; /* Access on call */
			} else if(!strcmp(aux->token, "IntLit") || !strcmp(aux->token, "ChrLit") || !strcmp(aux->token, "RealLit")){
				convert_types(aux, expected_type);
				param_array[params] = temporary_var-1;
			} else {
				code_gen(aux);
				convert_types(aux, expected_type);
				param_array[params] = temporary_var-1;
			}
		} else {
			if(!strcmp(aux->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, param_type, param_type);
				code_gen(aux);
				printf("\n");
				param_array[params] = temporary_var; /* Access on call */
				temporary_var++;
			} else if(is_expression(aux)){
				code_gen(aux);
				param_array[params] = temporary_var-1;
			} 
		}
		params++;
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
				if(!strcmp(aux->token, "IntLit") || !strcmp(aux->token, "ChrLit") || !strcmp(aux->token, "RealLit")){
					printf("%s ", expected_type);
					code_gen(aux);
					printf(")\n");
				} else {
					printf("%s %%%d)\n", expected_type, param_array[temp]);
				}
			} else {
				if(!strcmp(aux->token, "IntLit") || !strcmp(aux->token, "ChrLit") || !strcmp(aux->token, "RealLit")){
					printf("%s ", expected_type);
					code_gen(aux);
					printf(",\n");
				} else {
					printf("%s %%%d,\n", expected_type, param_array[temp]);
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
		printf("ret %s %%%d\n", type, temporary_var);
		temporary_var++;
	} else {
		printf("ret %s ", type);
		code_gen(node->child);
		printf("\n");
	}
}

void add_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	} else if(is_expression(node->child)){
		code_gen(node->child);
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
		}
		local_vars[0] = temporary_var-1;
	}		
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	} else if(is_expression(node->child->brother)){
		code_gen(node->child->brother);
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
		}
		local_vars[1] = temporary_var-1;
	}
	if(!strcmp(node->child->token, "Id") || is_expression(node->child) || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			if(!strcmp(result_type, "double")){
				printf("%%%d = fadd %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			} else {
				printf("%%%d = add %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			}
		} else {
			if(!strcmp(result_type, "double")){
				printf("%%%d = fadd %s %%%d, ", temporary_var, result_type, local_vars[0]);
			} else {
				printf("%%%d = add %s %%%d, ", temporary_var, result_type, local_vars[0]);
			}
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){  /* Second is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fadd %s ", temporary_var, result_type);
		} else {
			printf("%%%d = add %s ", temporary_var, result_type);	
		}
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fadd %s ", temporary_var, result_type);	
		} else {
			printf("%%%d = add %s ", temporary_var, result_type);	
		}
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void sub_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	} else if(is_expression(node->child)){
		code_gen(node->child);
		local_vars[0] = temporary_var-1;
	}		
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	} else if(is_expression(node->child->brother)){
		code_gen(node->child->brother);
		local_vars[1] = temporary_var-1;
	}
	if(!strcmp(node->child->token, "Id") || is_expression(node->child) || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			if(!strcmp(result_type, "double")){
				printf("%%%d = fsub %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			} else {
				printf("%%%d = sub %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			}
		} else {
			if(!strcmp(result_type, "double")){
				printf("%%%d = fsub %s %%%d, ", temporary_var, result_type, local_vars[0]);
			} else {
				printf("%%%d = sub %s %%%d, ", temporary_var, result_type, local_vars[0]);
			}
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){  /* Second is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fsub %s ", temporary_var, result_type);
		} else {
			printf("%%%d = sub %s ", temporary_var, result_type);	
		}
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fsub %s ", temporary_var, result_type);	
		} else {
			printf("%%%d = sub %s ", temporary_var, result_type);	
		}
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void mul_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	} else if(is_expression(node->child)){
		code_gen(node->child);
		local_vars[0] = temporary_var-1;
	}		
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	} else if(is_expression(node->child->brother)){
		code_gen(node->child->brother);
		local_vars[1] = temporary_var-1;
	}
	if(!strcmp(node->child->token, "Id") || is_expression(node->child) || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			if(!strcmp(result_type, "double")){
				printf("%%%d = fmul %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			} else {
				printf("%%%d = mul %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			}
		} else {
			if(!strcmp(result_type, "double")){
				printf("%%%d = fmul %s %%%d, ", temporary_var, result_type, local_vars[0]);
			} else {
				printf("%%%d = mul %s %%%d, ", temporary_var, result_type, local_vars[0]);
			}
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){  /* Second is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fmul %s ", temporary_var, result_type);
		} else {
			printf("%%%d = mul %s ", temporary_var, result_type);	
		}
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fmul %s ", temporary_var, result_type);	
		} else {
			printf("%%%d = mul %s ", temporary_var, result_type);	
		}
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void div_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	} else if(is_expression(node->child)){
		code_gen(node->child);
		local_vars[0] = temporary_var-1;
	}		
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	} else if(is_expression(node->child->brother)){
		code_gen(node->child->brother);
		local_vars[1] = temporary_var-1;
	}
	if(!strcmp(node->child->token, "Id") || is_expression(node->child) || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			if(!strcmp(result_type, "double")){
				printf("%%%d = fdiv %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			} else {
				printf("%%%d = sdiv %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
			}
		} else {
			if(!strcmp(result_type, "double")){
				printf("%%%d = fdiv %s %%%d, ", temporary_var, result_type, local_vars[0]);
			} else {
				printf("%%%d = sdiv %s %%%d, ", temporary_var, result_type, local_vars[0]);
			}
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother) || !strcmp(second_type, result_type)){  /* Second is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fdiv %s ", temporary_var, result_type);
		} else {
			printf("%%%d = sdiv %s ", temporary_var, result_type);	
		}
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		if(!strcmp(result_type, "double")){
			printf("%%%d = fdiv %s ", temporary_var, result_type);	
		} else {
			printf("%%%d = sdiv %s ", temporary_var, result_type);	
		}
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void mod_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->token, "Id") || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			printf("%%%d = srem %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
		} else {
			printf("%%%d = srem %s %%%d, ", temporary_var, result_type, local_vars[0]);
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){  /* Second is ID */
		printf("%%%d = srem %s ", temporary_var, result_type);
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		printf("%%%d = srem %s ", temporary_var, result_type);
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void or_gen(Node *node){
	or_cmp++;
	printf("\nbr label %%orfalse%d\n", or_cmp-1);
	printf("orfalse%d:\n", or_cmp-1);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(node->child->type), types_to_llvm(node->child->type));
		code_gen(node->child);
		printf("\n");
		temporary_var++;
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	} else if(!strcmp(node->child->token, "IntLit") || !strcmp(node->child->token, "ChrLit") || !strcmp(node->child->token, "RealLit")){
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %s, 0.000000e+00\n", temporary_var, node->child->value);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
				printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
			} else {
				printf("%%%d = icmp ne i32 %s, 0\n", temporary_var, node->child->value);
			}	
		}
		temporary_var++;
	} else {
		code_gen(node->child);
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	}
	printf("br i1 %%%d, label %%orend%d, label %%ortrue%d\n", temporary_var-1, or_cmp-1, or_cmp-1);
	printf("ortrue%d:\n", or_cmp-1);
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(node->child->brother->type), types_to_llvm(node->child->brother->type));
		code_gen(node->child->brother);
		printf("\n");
		temporary_var++;
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	} else if(!strcmp(node->child->brother->token, "IntLit") || !strcmp(node->child->brother->token, "ChrLit") || !strcmp(node->child->brother->token, "RealLit")){
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %s, 0.000000e+00\n", temporary_var, node->child->brother->value);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
				printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
			} else {
				printf("%%%d = icmp ne i32 %s, 0\n", temporary_var, node->child->brother->value);
			}	
		}
		temporary_var++;
	} else {
		code_gen(node->child->brother);
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	}
	printf("br label %%orend%d\n", or_cmp-1);
	printf("orend%d:\n", or_cmp-1);
	printf("%%%d = phi i1 [ true, %%orfalse%d ], [ %%%d, %%ortrue%d ]\n", temporary_var, or_cmp-1, temporary_var-1, or_cmp-1);
	temporary_var++;
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void and_gen(Node *node){
	and_cmp++;
	printf("\nbr label %%andfalse%d\n", and_cmp-1);
	printf("andfalse%d:\n", and_cmp-1);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(node->child->type), types_to_llvm(node->child->type));
		code_gen(node->child);
		printf("\n");
		temporary_var++;
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	} else if(!strcmp(node->child->token, "IntLit") || !strcmp(node->child->token, "ChrLit") || !strcmp(node->child->token, "RealLit")){
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %s, 0.000000e+00\n", temporary_var, node->child->value);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
				printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
			} else {
				printf("%%%d = icmp ne i32 %s, 0\n", temporary_var, node->child->value);
			}	
		}
		temporary_var++;
	} else {
		code_gen(node->child);
		if(!strcmp(types_to_llvm(node->child->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->type), "i32")){
				convert_types(node->child, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	}
	printf("br i1 %%%d, label %%andtrue%d, label %%andend%d\n", temporary_var-1, and_cmp-1, and_cmp-1);
	//code_gen(node->child->brother);
	printf("\nandtrue%d:\n", and_cmp-1);
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(node->child->brother->type), types_to_llvm(node->child->brother->type));
		code_gen(node->child->brother);
		printf("\n");
		temporary_var++;
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	} else if(!strcmp(node->child->brother->token, "IntLit") || !strcmp(node->child->brother->token, "ChrLit") || !strcmp(node->child->brother->token, "RealLit")){
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %s, 0.000000e+00\n", temporary_var, node->child->brother->value);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
				printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
			} else {
				printf("%%%d = icmp ne i32 %s, 0\n", temporary_var, node->child->brother->value);
			}	
		}
		temporary_var++;
	} else {
		code_gen(node->child->brother);
		if(!strcmp(types_to_llvm(node->child->brother->type), "double")){
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			if(strcmp(types_to_llvm(node->child->brother->type), "i32")){
				convert_types(node->child->brother, "i32");
			}
			printf("%%%d = icmp ne i32 %%%d, 0\n", temporary_var, temporary_var-1);
		}
		temporary_var++;
	}
	printf("br label %%andend%d\n", and_cmp-1);
	printf("\nandend%d:\n", and_cmp-1);
	printf("%%%d = phi i1 [ false, %%andfalse%d ], [ %%%d, %%andtrue%d ]\n", temporary_var, and_cmp-1, temporary_var-1, and_cmp-1);
	temporary_var++;
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void bitwiseand_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->token, "Id") || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			printf("%%%d = and %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
		} else {
			printf("%%%d = and %s %%%d, ", temporary_var, result_type, local_vars[0]);
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){  /* Second is ID */
		printf("%%%d = and %s ", temporary_var, result_type);
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		printf("%%%d = and %s ", temporary_var, result_type);
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void bitwiseor_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->token, "Id") || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			printf("%%%d = or %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
		} else {
			printf("%%%d = or %s %%%d, ", temporary_var, result_type, local_vars[0]);
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){  /* Second is ID */
		printf("%%%d = or %s ", temporary_var, result_type);
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		printf("%%%d = or %s ", temporary_var, result_type);
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void bitwisexor_gen(Node *node){
	int local_vars[2];
	char *first_type = node->child->type;
	char *second_type = node->child->brother->type;
	char *result_type = types_to_llvm(node->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(first_type), types_to_llvm(first_type));
		code_gen(node->child);
		printf("\n");
		local_vars[0] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(first_type), result_type)){
			convert_types(node->child, result_type);
			local_vars[0] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->brother->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, types_to_llvm(second_type), types_to_llvm(second_type));
		code_gen(node->child->brother);
		printf("\n");
		local_vars[1] = temporary_var;
		temporary_var++;
		if(strcmp(types_to_llvm(second_type), result_type)){
			convert_types(node->child->brother, result_type);
			local_vars[1] = temporary_var-1;
		}
	}
	if(!strcmp(node->child->token, "Id") || !strcmp(first_type, result_type)){ /* First is ID or different type */
		if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){ /* First + Second is ID or different type*/
			printf("%%%d = xor %s %%%d, %%%d\n", temporary_var, result_type, local_vars[0], local_vars[1]);
		} else {
			printf("%%%d = xor %s %%%d, ", temporary_var, result_type, local_vars[0]);
			code_gen(node->child); 
			printf("\n");
		}
	} else if(!strcmp(node->child->brother->token, "Id") || !strcmp(second_type, result_type)){  /* Second is ID */
		printf("%%%d = xor %s ", temporary_var, result_type);
		code_gen(node->child); 
		printf(", %%%d\n", local_vars[1]);
	} else { /* None is ID */
		printf("%%%d = xor %s ", temporary_var, result_type);
		code_gen(node->child);
		printf(", ");
		code_gen(node->child->brother);
		printf("\n");
	}
	temporary_var++;
}

void eq_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp oeq double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp oeq double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp oeq double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp oeq double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp eq %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp eq %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp eq %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp eq %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp oeq double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp oeq double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp oeq double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp oeq double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp eq %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp eq double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp eq double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp eq %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void ne_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp une double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp une double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp une double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp une double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp ne %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp ne %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp ne %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp ne %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp une double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp une double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp une double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp une double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp ne %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp ne double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp ne double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp ne %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void le_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp ole double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp ole double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp ole double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp ole double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp sle %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sle %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp sle %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sle %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp ole double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp ole double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp ole double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp ole double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp sle %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp sle double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp sle double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp sle %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void ge_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp oge double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp oge double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp oge double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp oge double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp sge %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sge %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp sge %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sge %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp oge double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp oge double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp oge double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp oge double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp sge %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp sge double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp sge double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp sge %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void lt_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp olt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp olt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp olt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp olt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp slt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp slt %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp slt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp slt %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp olt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp olt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp olt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp olt double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp slt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp slt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp slt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp slt %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void gt_gen(Node *node){
	int local_vars[2];
	char *first_type = types_to_llvm(node->child->type);
	char *second_type = types_to_llvm(node->child->brother->type);
	char *type = strdup(first_type);
	if(strcmp(first_type, second_type)){
		int greater = greater_type(first_type, second_type);
		if(greater == 1){
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
			type = strdup(first_type);
			convert_types(node->child->brother, first_type);
			local_vars[1] = temporary_var-1;
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
		} else {
			if(!strcmp(node->child->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
				code_gen(node->child);
				printf("\n");
				local_vars[0] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child)){
				code_gen(node->child);
				local_vars[0] = temporary_var-1;
			}
			type = strdup(second_type);
			convert_types(node->child, second_type);
			local_vars[0] = temporary_var-1;
			if(!strcmp(node->child->brother->token, "Id")){
				printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
				code_gen(node->child->brother);
				printf("\n");
				local_vars[1] = temporary_var;
				temporary_var++;
			} else if(is_expression(node->child->brother)){
				code_gen(node->child->brother);
				local_vars[1] = temporary_var-1;
			}
		}
		if(!strcmp(type, "double")){
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = fcmp ogt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp ogt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = fcmp ogt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = fcmp ogt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			}
		} else {
			if(greater == 1){
				if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
					printf("%%%d = icmp sgt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sgt %s %s, %%%d\n", temporary_var, type, node->child->value, local_vars[1]);
				}
			} else {
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){
					printf("%%%d = icmp sgt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* Is another terminal */
					printf("%%%d = icmp sgt %s %%%d, %s\n", temporary_var, type, local_vars[0], node->child->brother->value);
				}
			}
		}
		temporary_var++;
	} else {
		if(!strcmp(node->child->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, first_type, first_type);
			code_gen(node->child);
			printf("\n");
			local_vars[0] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child)){
			code_gen(node->child);
			local_vars[0] = temporary_var-1;
		}
		if(!strcmp(node->child->brother->token, "Id")){
			printf("%%%d = load %s, %s* ", temporary_var, second_type, second_type);
			code_gen(node->child->brother);
			printf("\n");
			local_vars[1] = temporary_var;
			temporary_var++;
		} else if(is_expression(node->child->brother)){
			code_gen(node->child->brother);
			local_vars[1] = temporary_var-1;
		}
		if(!strcmp(type, "double")) {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = fcmp ogt double %%%d, %%%d\n", temporary_var, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = fcmp ogt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = fcmp ogt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = fcmp ogt double %s, %s\n", temporary_var, node->child->value, node->child->brother->value);
			}
		} else {
			if(!strcmp(node->child->token, "Id") || is_expression(node->child)){
				if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){  /* First and Second are ID */
					printf("%%%d = icmp sgt %s %%%d, %%%d\n", temporary_var, type, local_vars[0], local_vars[1]);
				} else { /* First is ID */
					printf("%%%d = icmp sgt double %%%d, %s\n", temporary_var, local_vars[0], node->child->brother->value);
				}
			} else if(!strcmp(node->child->brother->token, "Id") || is_expression(node->child->brother)){ /* Second is ID */
				printf("%%%d = icmp sgt double %s, %%%d\n", temporary_var, node->child->value, local_vars[1]);
			} else {
				printf("%%%d = icmp sgt %s %s, %s\n", temporary_var, type, node->child->value, node->child->brother->value);
			}
		}
		temporary_var++;
	}	
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

void not_gen(Node *node){
	char *type = types_to_llvm(node->child->type);
	if(!strcmp(node->child->token, "Id")){
		printf("%%%d = load %s, %s* ", temporary_var, type, type);
		code_gen(node->child);
		printf("\n");
		temporary_var++;
	} else if(is_expression(node->child)){
		code_gen(node->child);
	}
	if(!strcmp(type, "double")){
		if(!strcmp(node->child->token, "Id") || is_expression(node->child)) {
			printf("%%%d = fcmp une double %%%d, 0.000000e+00\n", temporary_var, temporary_var-1);
		} else {
			printf("%%%d = fcmp une double %s, 0.000000e+00\n", temporary_var, node->child->value);
		}
	} else {
		if(!strcmp(node->child->token, "Id") || is_expression(node->child)) {
			printf("%%%d = icmp ne %s %%%d, 0\n", temporary_var, type, temporary_var-1);
		} else {
			printf("%%%d = icmp ne %s %s, 0\n", temporary_var, type, node->child->value);
		}
	}
	temporary_var++;
	printf("%%%d = xor i1 %%%d, true\n", temporary_var, temporary_var-1);
	temporary_var++;
	printf("%%%d = zext i1 %%%d to i32\n", temporary_var, temporary_var-1);
	temporary_var++;
}

int is_global(char *name){
	Symbol *aux = global->symbol;
	while(aux){ /* Checks if is global */
		if(!strcmp(aux->name, name)){
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}

int is_expression(Node *node){
	if(!strcmp(node->token, "Add") || !strcmp(node->token, "Sub") || !strcmp(node->token, "Mul") || !strcmp(node->token, "Div") || !strcmp(node->token, "Mod") || !strcmp(node->token, "Eq") || !strcmp(node->token, "Ne") || !strcmp(node->token, "Gt") || !strcmp(node->token, "Lt") || !strcmp(node->token, "Ge") || !strcmp(node->token, "Le") || !strcmp(node->token, "And") || !strcmp(node->token, "Or") || !strcmp(node->token, "BitWiseAnd") || !strcmp(node->token, "BitWiseOr") || !strcmp(node->token, "BitWiseXor")){
		return 1;
	}
	return 0;
}

int greater_type(char *first, char *second){
	if(!strcmp(second, "double") && strcmp(first, "double")){
		return 2;
	} else if(!strcmp(first, "double") && strcmp(second, "double")){
		return 1;
	} else if(!strcmp(first, "i32") && (!strcmp(second, "i16") || !strcmp(second, "i8"))){
		return 1;
	} else if(!strcmp(second, "i32") && (!strcmp(first, "i16") || !strcmp(first, "i8"))){
		return 2;
	} else if(!strcmp(first, "i16") && !strcmp(second, "i8")){
		return 1;
	} else if(!strcmp(second, "i16") && !strcmp(first, "i8")){
		return 2;
	}
	return -1;
}

void convert_types(Node *received, char *expected){
	if((!strcmp(received->type, "char") || !strcmp(received->type, "short") || !strcmp(received->type, "int")) && !strcmp(expected, "double")){
		if(strcmp(received->type, "int")){
			if(!strcmp(received->token, "IntLit") || !strcmp(received->token, "ChrLit") || !strcmp(received->token, "RealLit")){
				printf("%%%d = sext ", temporary_var);
				code_gen(received);
				printf(" to %s\n", expected);
			} else {
				printf("%%%d = sext %s %%%d to i32\n", temporary_var, types_to_llvm(received->type), temporary_var-1);
			}
			temporary_var++;
		}
		printf("%%%d = sitofp i32 %%%d to %s\n", temporary_var, temporary_var-1, expected);
	} else if(((!strcmp(received->type, "int") || !strcmp(received->type, "short")) && !strcmp(expected, "i8")) || (!strcmp(received->type, "int") && !strcmp(expected, "i16"))){ /* Expected char - Got int, short || Expected short - Got int*/
		if(!strcmp(received->token, "IntLit") || !strcmp(received->token, "ChrLit") || !strcmp(received->token, "RealLit")){
			printf("%%%d = trunc %s ", temporary_var, types_to_llvm(received->type));
			code_gen(received);
			printf(" to %s\n", expected);
		} else {
			printf("%%%d = trunc %s %%%d to %s\n", temporary_var, types_to_llvm(received->type), temporary_var-1, expected);
		}
	} else if((!strcmp(expected, "i8") || !strcmp(expected, "i16") || !strcmp(expected, "i32")) && !strcmp(received->type, "double")){ /* Expected char, short, int - Got double */
		if(!strcmp(received->token, "IntLit") || !strcmp(received->token, "ChrLit") || !strcmp(received->token, "RealLit")){
			printf("%%%d = fptosi double ", temporary_var);
			code_gen(received);
			printf(" to %s\n", expected);
		} else {
			printf("%%%d = fptosi double %%%d to %s\n", temporary_var, temporary_var-1, expected);
		}
	} else {
		if(!strcmp(received->token, "IntLit") || !strcmp(received->token, "ChrLit") || !strcmp(received->token, "RealLit")){
			printf("%%%d = sext ", temporary_var);
			code_gen(received);
			printf(" to %s\n", expected);
		} else {
			printf("%%%d = sext %s %%%d to %s\n", temporary_var, types_to_llvm(received->type), temporary_var-1, expected);
		}
	}
	temporary_var++;
}