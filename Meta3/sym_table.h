#include "tree.h"

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol Symbol;
typedef struct Param Param;
typedef struct Symbol_Table Symbol_Table;

struct Symbol{
    char *name;
    char *type;
    Param *param;
    Symbol *next;
};

struct Param{
	char *name;
	char *type;
	Param *next;
};

struct Symbol_Table{
	char *title;
	int definition;
	Symbol_Table *next;
	Symbol *symbol;
};

Symbol_Table* sym_table;
Symbol_Table* create_table(char *title);
Symbol* create_symbol(char *name, char *type);
void insert_symbol(Symbol_Table *table, Symbol *symbol);
Symbol_Table* create_default_table();
Param* insert_param(Symbol *sym, char *name, char *type);
void print_params(Symbol *symbol);
void print_table(Symbol_Table *table);
void parse_table(Node *node, Symbol_Table *table);
void parse_func_declaration(Node *node, Symbol_Table *global);
void parse_func_definition(Node *node, Symbol_Table *global);
void parse_declaration(Node *node, Symbol_Table *global);
void add_return(Symbol_Table *table, char *type);
void print_all_tables(Symbol_Table *table);
char *lower_case(char *str);
#endif //SYMBOL_TABLE_H
