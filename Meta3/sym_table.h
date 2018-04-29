#include "tree.h"
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol Symbol;
typedef struct Symbol_Table Symbol_Table;

struct Symbol{
    char *name;
    char *type;
	int is_param;
    Param *param;
    Symbol *next;
};

struct Symbol_Table{
	char *title;
	char *name;
	int definition;
	Symbol_Table *next;
	Symbol *symbol;
};

Symbol_Table* sym_table;
Symbol_Table* create_table(char *title, char *name);
Symbol* create_symbol(char *name, char *type);
void insert_symbol(Symbol_Table *table, Symbol *symbol);
Symbol_Table* create_default_table();
Param* insert_param(Symbol *sym, char *name, char *type);
void print_params(Symbol *symbol);
void print_table(Symbol_Table *table);
void parse_table(Node *node, Symbol_Table *table);
void parse_func_declaration(Node *node, Symbol_Table *global);
void parse_func_definition(Node *node, Symbol_Table *global);
void find_declaration(Node *node, Symbol_Table *local);
void parse_declaration(Node *node, Symbol_Table *global, int recursive);
void add_return(Symbol_Table *table, char *type);
void print_all_tables(Symbol_Table *table);
char *lower_case(char *str);
void annotated_tree(Node *root, Symbol_Table *local, Symbol_Table *global);
int add_type(Node *node, Symbol_Table *local, Symbol_Table *global);
void add_unary_type(Node *node, Symbol_Table *local, Symbol_Table *global);
void add_comparison_type(Node *node, Symbol_Table *local, Symbol_Table *global);
void add_call_type(Node *node, Symbol_Table *local, Symbol_Table *global);
//char* add_id_type_function(Node *node, Symbol_Table *local, Symbol_Table *global);
char* add_id_type(Node *node, Symbol_Table *local, Symbol_Table *global);
void add_literal_type(Node *node, Symbol_Table *local, Symbol_Table *global);
void add_declaration_types(Node *node, Symbol_Table *local, Symbol_Table *global);
char* type_compare(char *ftype, char *stype, char *token);
#endif //SYMBOL_TABLE_H
