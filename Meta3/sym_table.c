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
		param->name = strdup(name);
	} else {
		param->name = NULL;
	}
	param->type = strdup(type);
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
	sym->name = strdup(name);
	sym->type = strdup(type);
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
		printf("%s %s",aux->name, aux->type);
		print_params(aux);
		while(aux->next != NULL){
			aux = aux->next;
			printf("%s %s",aux->name, aux->type);
			print_params(aux);
		}
	}
}

void print_all_tables(Symbol_Table *table){
	Symbol_Table *aux_table = table;
	while(aux_table != NULL){
		print_table(aux_table);
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
				//parse_func_defin
			} else if(strcmp(aux->token, "Declaration") == 0){
				//parse_declar
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
	while(symbol_aux != NULL) {
		if(strcmp(name, symbol_aux->name) == 0){ // Was already declared
			return;
		}
		symbol_aux = symbol_aux->next;
	}
	char *name_aux = malloc((strlen("Function") + strlen(name) + strlen("Symbol Table")) * sizeof(char));
	sprintf(name_aux, "%s %s %s","Function", name, "Symbol Table");
	table_aux = create_table(name_aux);
	while(global_aux->next != NULL){
		global_aux = global_aux->next;
	}
	global_aux->next = table_aux;
	while(strcmp(node_aux->token, "ParamList") != 0){
		node_aux = node_aux->brother;
	}
	if(node_aux == NULL){
		return;
	}
	node_aux = node_aux->child;
	symbol_aux = create_symbol(name, type);
	while(node_aux != NULL){
		if(node_aux->child->brother != NULL){ // Se tiver id
			insert_param(symbol_aux, node_aux->child->brother->value, node_aux->child->token);
		} else {
			insert_param(symbol_aux, NULL, node_aux->child->token);
		}
		node_aux = node_aux->brother;
	}
	insert_symbol(global, symbol_aux);
}

/*int main(){
	Symbol_Table *table = create_default_table();
	print_all_tables(table);
	return 0;
}*/

