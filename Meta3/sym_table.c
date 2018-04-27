#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_table.h"

Symbol_Table* create_table(char *title){
	Symbol_Table* table = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	table->title = strdup(title);
	table->next = NULL;
	table->symbol = NULL;
	return table;
}

Param* insert_param(Symbol *sym, char *name, char *type){
	Param* param = (Param*) malloc(sizeof(Param));
	Param* aux;
	if(name != NULL){
		param->name = lower_case(name);
	} else {
		param->name = NULL;
	}
	param->type = lower_case(type);
	param->next = NULL;
	if(sym->param == NULL){
		sym->param = param;
	} else {
		aux = sym->param;
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = param; 
	}
	return param;
}

Symbol* create_symbol(char *name, char *type){
	Symbol *sym = (Symbol*) malloc(sizeof(Symbol));
	sym->name = lower_case(name);
	sym->type = lower_case(type);
	sym->param = NULL;
	sym->next = NULL;
	return sym;
}

void insert_symbol(Symbol_Table *table, Symbol *symbol) {
	Symbol *aux;
    if(table == NULL) /* If table to insert is null end function */
        return;
    if(table->symbol == NULL){ /* If table has no symbol, create one */
        table->symbol = symbol;
    } else {
        aux = table->symbol;
        while (aux->next != NULL){ /* Goes through all the symbols */
            aux = aux->next;
        }
        aux->next=symbol;
		aux->next->next = NULL;
    }
}

void print_params(Symbol *symbol){
	if(symbol != NULL){
		printf("(");
		Param *aux = symbol->param;
		if(aux != NULL){
			printf("%s", aux->type);
			aux = aux->next;
		}
		while(aux != NULL){
			printf(", %s", aux->type);
			aux = aux->next;
		}
		printf(")\n");
	}
}

void print_table(Symbol_Table *table){
	printf("===== %s =====\n", table->title);
	if(table->symbol != NULL){
		Symbol *aux = table->symbol;
		printf("%s\t%s",aux->name, aux->type);
		if(aux->param != NULL){
			print_params(aux);
		} else{
			printf("\n");
		}
		while(aux->next != NULL){
			aux = aux->next;
			printf("%s\t%s",aux->name, aux->type);
			if(aux->param != NULL){
				print_params(aux);
			} else{
				printf("\n");
			}
		}
	}
}

void print_all_tables(Symbol_Table *table){
	Symbol_Table *aux_table = table;
	while(aux_table != NULL){
		print_table(aux_table);
		if(aux_table->next != NULL){
			printf("\n");
		}
		aux_table = aux_table->next;
	}
}

Symbol_Table* create_default_table(){
	Symbol *sym_aux;
	Symbol_Table *global = create_table("Global Symbol Table");
	sym_aux = create_symbol("putchar", "int");
	insert_param(sym_aux, NULL, "int");
	insert_symbol(global, sym_aux);
	sym_aux = create_symbol("getchar", "int");
	insert_param(sym_aux, NULL, "void");
	insert_symbol(global, sym_aux);
	return global;
}

void parse_table(Node *node, Symbol_Table *table){
	Node *aux = node->child;
	if(aux == NULL){
		return;
	} else {
		while(aux != NULL){
			if(strcmp(aux->token, "FuncDeclaration") == 0){
				parse_func_declaration(aux, table);
			} else if(strcmp(aux->token, "FuncDefinition") == 0){
				parse_func_definition(aux, table);
			} else if(strcmp(aux->token, "Declaration") == 0){
				parse_declaration(aux, table);
			}
			aux = aux->brother;
		}
	}
}

void parse_func_declaration(Node *node, Symbol_Table *global){
	Symbol_Table *table_aux, *global_aux = global;
	Node *node_aux = node->child;
	char *type = node_aux->token;
	char *name = node_aux->brother->value;
	Symbol *symbol_aux;
	symbol_aux = global->symbol;
	while(symbol_aux != NULL) { // Goes through global symbol table to see if function was already declared
		if(strcmp(name, symbol_aux->name) == 0){ // Was already declared
			return;
		}
		symbol_aux = symbol_aux->next;
	}
	char *name_aux = malloc((strlen("Function") + strlen(name) + strlen("Symbol Table")) * sizeof(char));
	sprintf(name_aux, "%s %s %s","Function", name, "Symbol Table");
	table_aux = create_table(name_aux); // Create symbol table for current function
	while(global_aux->next != NULL){ // Adds table to global table brothers
		global_aux = global_aux->next;
	}
	global_aux->next = table_aux;
	while(strcmp(node_aux->token, "ParamList") != 0){ // Skips type and name
		node_aux = node_aux->brother;
	}
	if(node_aux == NULL){
		return;
	}
	node_aux = node_aux->child; // Skip ParamList
	symbol_aux = create_symbol(name, type);
	while(node_aux != NULL){ // Check if there are more ParamDeclaration
		if(node_aux->child->brother != NULL){ // Checks if param has id
			insert_param(symbol_aux, node_aux->child->brother->value, node_aux->child->token);
		} else {
			insert_param(symbol_aux, NULL, node_aux->child->token);
		}
		node_aux = node_aux->brother;
	}
	insert_symbol(global, symbol_aux); // Add function to global symbol table
	add_return(table_aux, type);	
}

void parse_func_definition(Node *node, Symbol_Table *global){
	Symbol_Table *table_aux, *global_aux = global;
	Node *node_aux = node->child;
	Node *node_sec_aux;
	char *type = node_aux->token;
	char *name = node_aux->brother->value;
	Symbol *symbol_aux;
	Symbol *symbol_sec_aux;
	symbol_aux = global->symbol;
	while(symbol_aux != NULL) { // Goes through global symbol table to see if function was already declared
		if(strcmp(name, symbol_aux->name) == 0){ // Was already declared
			return;
		}
		symbol_aux = symbol_aux->next;
	}
	char *name_aux = malloc((strlen("Function") + strlen(name) + strlen("Symbol Table")) * sizeof(char));
	sprintf(name_aux, "%s %s %s","Function", name, "Symbol Table");
	table_aux = create_table(name_aux); // Create symbol table for current function
	while(global_aux->next != NULL){ // Adds table to global table brothers
		global_aux = global_aux->next;
	}
	global_aux->next = table_aux;
	while(strcmp(node_aux->token, "ParamList") != 0){ // Skips type and name
		node_aux = node_aux->brother;
	}
	if(node_aux == NULL){
		return;
	}
	node_sec_aux = node_aux->child; // Skip ParamList
	symbol_aux = create_symbol(name, type);
	while(node_sec_aux != NULL){ // Check if there are more ParamDeclaration
		if(node_sec_aux->child->brother != NULL){ // Checks if param has id
			insert_param(symbol_aux, node_sec_aux->child->brother->value, node_sec_aux->child->token);
		} else {
			insert_param(symbol_aux, NULL, node_sec_aux->child->token);
		}
		node_sec_aux = node_sec_aux->brother;
	}
	node_aux = node_aux->brother;
	if(strcmp(node_aux->token, "FuncBody") != 0){
		return;
	}
	node_sec_aux = node_aux->child; // Skips FuncBody
	while(node_sec_aux != NULL){ // Goes through FuncBody children
		if(strcmp(node_sec_aux->token, "Declaration") == 0){ // Found Declaration
			symbol_sec_aux = (Symbol*) malloc(sizeof(Symbol));
			symbol_sec_aux->type = lower_case(node_sec_aux->child->token);
			symbol_sec_aux->name = lower_case(node_sec_aux->child->brother->value);
			symbol_sec_aux->param = NULL;
			symbol_sec_aux->next = NULL;
			insert_symbol(table_aux, symbol_sec_aux);
		}
		node_sec_aux = node_sec_aux->brother;
	}
	insert_symbol(global, symbol_aux); // Add function to global symbol table
	add_return(table_aux, type);
}

void add_return(Symbol_Table *table, char *type){
	Symbol *symbol_aux = (Symbol*) malloc(sizeof(Symbol));
	symbol_aux->name = strdup("return");
	symbol_aux->type = lower_case(type);
	insert_symbol(table, symbol_aux); // Add return to function
}
void parse_declaration(Node *node, Symbol_Table *global){
	Symbol *symbol_aux = (Symbol*) malloc(sizeof(Symbol));
	Node *node_aux = node; // Skip Declaration
	symbol_aux->type = lower_case(node_aux->child->token);
	symbol_aux->name = lower_case(node_aux->child->brother->value);
	symbol_aux->param = NULL;
	symbol_aux->next = NULL;
	insert_symbol(global, symbol_aux);
}

char *lower_case(char *str){
	char *aux = strdup(str);
	if(aux[0] >= 'A' && aux[0] <= 'Z'){
		aux[0] += 'a' - 'A';
	}
	return aux;
}

/*int main(){
	Symbol_Table *table = create_default_table();
	print_all_tables(table);
	return 0;
}*/

