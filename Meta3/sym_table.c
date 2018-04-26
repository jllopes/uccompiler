#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_table.h"

Symbol_Table* create_table(char *title){
	Symbol_Table* table = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	table->title = (char*) malloc(sizeof(title)* sizeof(char));
	strcpy(table->title, title);
	table->next = NULL;
	return table;
}

Symbol_Table* insert_symbol(Symbol_Table *table, Symbol *symbol) {
	symbol->next = NULL;
    if(table == NULL) /* If table to insert is null end function */
        return NULL;
    if(table->symbol == NULL){ /* If table has no symbol, create one */
        printf("!.\n");
        table->symbol = symbol;
    } else {
        Symbol *tmp = (Symbol*) malloc(sizeof(Symbol));
        Symbol *prev = (Symbol*) malloc(sizeof(Symbol));
        prev = table->symbol;
        printf("!\n");
        tmp = table->symbol->next;
        printf("!\n");
        while (tmp != NULL){ /* Goes through all the symbols */
            prev = tmp;
            tmp = tmp->next;
        }
        printf("!\n");
        prev->next = (Symbol*) malloc(sizeof(Symbol));
        printf("!\n");
        prev->next=symbol;
    }
    return table;
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



int main(){
	Symbol_Table *table = create_table("Test Symbol Table");
	table->next = create_table("Test2 Symbol Table");
	Symbol *symbol = (Symbol*) malloc(sizeof(Symbol));
	symbol->name = (char*) malloc(sizeof(char) * 12);
	char *aux = "asdfasdf";
	char *aux2 = "asdfasdf2";
	symbol->type = (char*) malloc(sizeof(char) * 12);
	strcpy(symbol->type, aux);
	strcpy(symbol->name, aux2);
	insert_symbol(table, symbol);
	print_all_tables(table);
}