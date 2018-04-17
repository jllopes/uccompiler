#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol Symbol;
typedef struct Param Param;
typedef struct Symbol_Table Symbol_Table;

struct Symbol{
    char *name;
    char *type;
    Param *param;
    int param_num;
    Symbol *next;
};

struct Param{
	char *name;
	char *type;
	Param *next;
}

struct Symbol_Table{
	char *title;
	int definition;
	Symbol_Table *next;
	Symbol *symbol;
}

#endif //SYMBOL_TABLE_H
