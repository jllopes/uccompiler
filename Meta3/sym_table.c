#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_table.h"

Symbol_Table* create_table(int type, char *name){
	Symbol_Table* table = (Symbol_Table*) malloc(sizeof(Symbol_Table));
	table->type = type;
	if(name != NULL){
		table->name = strdup(name);
	} else {
		table->name = NULL;
	}
	table->next = NULL;
	table->symbol = NULL;
	return table;
}

Param* insert_param(Symbol *sym, char *name, char *type){
	Param* param = (Param*) malloc(sizeof(Param));
	Param* aux = (Param*) malloc(sizeof(Param));
	if(name != NULL){
		param->name = strdup(name);
	} else {
		param->name = NULL;
	}
	param->type = strdup(lower_case(type));
	param->next = NULL;
	if(sym->param == NULL){
		sym->param = param;
	} else {
		aux = sym->param;
		while(aux != NULL){
			if(aux->next == NULL)
				break;
			aux = aux->next;
		}
		aux->next = param; 
	}
	return param;
}

Symbol* create_symbol(char *name, char *type){
	Symbol *sym = (Symbol*) malloc(sizeof(Symbol));
	sym->name = strdup(name);
	sym->type = strdup(lower_case(type));
	sym->param = NULL;
	sym->is_param = 0;
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
        //printf("inserting: %s\n", symbol->name);
        while (aux != NULL){ /* Goes through all the symbols */
        	//printf("found: %s\n", aux->name);
        	if(strcmp(symbol->name, aux->name) == 0){
        		return;
        	}
        	if(aux->next == NULL)
        		break;
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
			printf(",%s", aux->type);
			aux = aux->next;
		}
		printf(")");
	}
}

void print_table(Symbol_Table *table){
	if(table->type == 0){
		printf("===== Global Symbol Table =====\n");
	} else if(table->type == 1){
		printf("===== Function %s Symbol Table =====\n", table->name);
	}
	if(table->symbol != NULL){
		Symbol *aux = table->symbol;
		if(aux->is_param == 1){
			printf("%s\t%s\tparam\n",aux->name, aux->type);
		} else {
			printf("%s\t%s",aux->name, aux->type);
			if(aux->param != NULL){
				print_params(aux);
			}
			printf("\n");
		}
		while(aux->next != NULL){
			aux = aux->next;
			if(aux->is_param == 1){
				printf("%s\t%s\tparam\n",aux->name, aux->type);
			} else {
				printf("%s\t%s",aux->name, aux->type);
				if(aux->param != NULL){
					print_params(aux);
				}
				printf("\n");
			}
		}
	}
}

void print_all_tables(Symbol_Table *table){
	Symbol_Table *aux_table = table;
	while(aux_table != NULL){
		if(aux_table->definition != 0){
			print_table(aux_table);
			printf("\n");
		}
		aux_table = aux_table->next;
	}
}

Symbol_Table* create_default_table(){
	Symbol *sym_aux;
	Symbol_Table *global = create_table(0, NULL);
	sym_aux = create_symbol("putchar", "int");
	insert_param(sym_aux, NULL, "int");
	insert_symbol(global, sym_aux);
	sym_aux = create_symbol("getchar", "int");
	insert_param(sym_aux, NULL, "void");
	insert_symbol(global, sym_aux);
	global->definition = 1;
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
				parse_declaration(aux, table, 0);
			}
			if(aux->brother == NULL)
				break;
			aux = aux->brother;
		}
	}
}

void parse_func_declaration(Node *node, Symbol_Table *global){
	Symbol_Table *table_aux = (Symbol_Table*) malloc(sizeof(Symbol_Table)), *global_aux = global;
	Node *node_aux = node->child; // Skips FuncDeclaration node
	char *type = strdup(node_aux->token); // Copies type to aux variable
	char *name = strdup(node_aux->brother->value); // Copies name to aux variable
	Symbol *symbol_aux = (Symbol*)malloc(sizeof(Symbol));
	symbol_aux = global->symbol; // Finds first symbol on global table (never null because of default functions)
	while(symbol_aux != NULL) { // Goes through global symbol table to see if function was already declared
		if(strcmp(name, symbol_aux->name) == 0){ // Was already declared
			return;
		}
		if(symbol_aux->next == NULL)
			break;
		symbol_aux = symbol_aux->next;
	}
	symbol_aux = create_symbol(name, type); // Create function symbol to add to global table
	table_aux = create_table(1, name); // Create symbol table for current function
	// Table is create here to make sure it appears before next FuncDefinition, won't be printed if the functions isn't defined
	add_return(table_aux, type); // Adds return type to local table
	while(global_aux->next != NULL){ // Adds table to global table brothers
		global_aux = global_aux->next;
	}
	global_aux->next = table_aux; // Add local table to global brothers
	table_aux->definition = 0; // It's a declaration, variable says the functions hasn't yet been defined
	while(strcmp(node_aux->token, "ParamList") != 0){ // Skips type and name
		node_aux = node_aux->brother;
	}
	if(node_aux == NULL){
		return;
	}
	node_aux = node_aux->child; // Skip ParamList, node_aux is now the first ParamDeclaration (1 is mandatory)
	while(node_aux != NULL){ // Check if there are more ParamDeclaration
		if(node_aux->child->brother != NULL){ // Checks if param has id
			Symbol *symbol_sec_aux = (Symbol*) malloc(sizeof(Symbol));
			insert_param(symbol_aux, node_aux->child->brother->value, node_aux->child->token);
			symbol_sec_aux->name = strdup(node_aux->child->brother->value);
			symbol_sec_aux->type = strdup(lower_case(node_aux->child->token));
			symbol_sec_aux->is_param = 1;
			insert_symbol(table_aux, symbol_sec_aux); // Insert param on local table
		} else {
			insert_param(symbol_aux, NULL, node_aux->child->token);
		}
		if(node_aux->brother == NULL)
			break;
		node_aux = node_aux->brother;
	}
	insert_symbol(global, symbol_aux); // Add function to global symbol table
}

void parse_func_definition(Node *node, Symbol_Table *global){
	Symbol_Table *table_aux = (Symbol_Table*)malloc(sizeof(Symbol_Table)), *global_aux = global->next;
	Node *node_aux = node->child; // First child of FuncDefinition
	Node *node_sec_aux;
	char *type = strdup(node_aux->token); // Return type
	char *name = strdup(node_aux->brother->value); // Value of Id
	Symbol *symbol_aux = (Symbol*)malloc(sizeof(Symbol));
	Symbol *symbol_sec_aux = (Symbol*) malloc(sizeof(Symbol));
	int declared = 0;
	while(global_aux != NULL) { // Goes through global symbol table to see if function was already declared
		if(strcmp(name, global_aux->name) == 0){ // Was already declared
			declared = 1; // To check if there is a need to create local table
			table_aux = global_aux;
			if(global_aux->definition == 1){ // Was already defined, prevents duplicated definitions
				return;
			}
		}
		global_aux = global_aux->next;
	}
	global_aux = global;
	if(declared == 0){ // Function hasn't been declared yet
		table_aux = create_table(1, name); // Create symbol table for current function
		add_return(table_aux, type);
		while(global_aux->next != NULL){ // Adds table to global table brothers
			global_aux = global_aux->next;
		}
		global_aux->next = table_aux; // Add local table to global brothers
		while(strcmp(node_aux->token, "ParamList") != 0){ // Skips type and name
			node_aux = node_aux->brother;
		}
		if(node_aux == NULL){
			return;
		}
		node_sec_aux = node_aux->child; // Skip ParamList
		symbol_aux = create_symbol(name, type); // Creates symbol to add to global table
		insert_symbol(global, symbol_aux); // Add function to global symbol table
		while(node_sec_aux != NULL){ // Check if there are more ParamDeclaration
			if(node_sec_aux->child->brother != NULL){ // Checks if param has id
				insert_param(symbol_aux, node_sec_aux->child->brother->value, node_sec_aux->child->token);
				symbol_sec_aux = (Symbol*) malloc(sizeof(Symbol));
				symbol_sec_aux->name = strdup(node_sec_aux->child->brother->value);
				symbol_sec_aux->type = strdup(lower_case(node_sec_aux->child->token));
				symbol_sec_aux->is_param = 1;
				insert_symbol(table_aux, symbol_sec_aux);
			} else {
				insert_param(symbol_aux, NULL, node_sec_aux->child->token);
			}
			node_sec_aux = node_sec_aux->brother;
		}
	} else {
		global_aux = global->next; // Skips global table
		while(global_aux != NULL){
			if(strcmp(name, global_aux->name) == 0) {
				table_aux = global_aux;
			}
			global_aux = global_aux->next;
		}
		while(strcmp(node_aux->token, "ParamList") != 0){
			node_aux = node_aux->brother;
		}
		table_aux->symbol->next = NULL;
		node_sec_aux = node_aux->child; // Skip ParamList
		while(node_sec_aux != NULL){
			if(node_sec_aux->child->brother != NULL){ // Param has id, is added to local table
				symbol_sec_aux = (Symbol*) malloc(sizeof(Symbol));
				symbol_sec_aux->name = strdup(node_sec_aux->child->brother->value);
				symbol_sec_aux->type = strdup(lower_case(node_sec_aux->child->token));
				symbol_sec_aux->is_param = 1;
				insert_symbol(table_aux, symbol_sec_aux);
			}
			node_sec_aux = node_sec_aux->brother;
		}
	}
	table_aux->definition = 1;
	while(strcmp(node_aux->token, "FuncBody") != 0){
		node_aux = node_aux->brother;
	}
	node_sec_aux = node_aux->child; // Skips FuncBody
	/*while(node_sec_aux != NULL){ // Goes through FuncBody children
		if(strcmp(node_sec_aux->token, "Declaration") == 0){ // Found Declaration
			parse_declaration(node_sec_aux, table_aux, 1);
		}
		node_sec_aux = node_sec_aux->brother;
	}*/
	if(node_sec_aux != NULL){
		find_declaration(node_sec_aux, table_aux); // Finds declarations inside of ifs and whiles
	}
	annotated_tree(node_aux, table_aux, global);
}

void find_declaration(Node *node, Symbol_Table *local){
	Node *node_aux = node;
	//printf("%s\n", node_aux->token);
	while(node_aux != NULL){ // Goes through FuncBody children
		if(strcmp(node_aux->token, "Declaration") == 0){ // Found declaration
			parse_declaration(node_aux, local, 1);
		} else if(node_aux->child != NULL){ // Found condition
			find_declaration(node_aux->child, local); // Recursive call
		}
		node_aux = node_aux->brother;
	}
}

void add_return(Symbol_Table *table, char *type){
	Symbol *symbol_aux = (Symbol*) malloc(sizeof(Symbol));
	symbol_aux->name = strdup("return");
	symbol_aux->type = strdup(lower_case(type));
	insert_symbol(table, symbol_aux); // Add return to function
}

void parse_declaration(Node *node, Symbol_Table *table, int recursive){
	Symbol *symbol_aux = (Symbol*) malloc(sizeof(Symbol));
	Symbol *symbol_sec_aux = table->symbol;
	Node *node_aux = node;
	while(symbol_sec_aux != NULL) { // Goes through symbol table to see if variable was already declared
		if(strcmp(node_aux->child->brother->value, symbol_sec_aux->name) == 0){ // Was already declared
			/* Symbol <token> already defined */ // SEMANTIC
			//printf("Line %d, col %d: Symbol %s already defined\n", node_aux->child->brother->line, (int)((node_aux->child->brother->column)-strlen(node->child->brother->value)), node->child->brother->value);
			return;
		}
		symbol_sec_aux = symbol_sec_aux->next;
	}
	symbol_aux->type = strdup(lower_case(node_aux->child->token)); // Type
	symbol_aux->name = strdup(node_aux->child->brother->value); // Name [Id(x) -> x = name = value]
	symbol_aux->param = NULL;
	symbol_aux->is_param = 0;
	symbol_aux->next = NULL;
	insert_symbol(table, symbol_aux);
	if(!recursive){
		annotated_tree(node, table, table);
	}
}

char *lower_case(char *str){
	char *aux = strdup(str);
	if(aux[0] >= 'A' && aux[0] <= 'Z'){
		aux[0] += 'a' - 'A';
	}
	return aux;
}

void annotated_tree(Node *root, Symbol_Table *local, Symbol_Table *global) {
    Node *node = root;
    //printf("Token:%s, Value:%s\n", node->token, node->value);
    while(node != NULL) {
		int result = add_type(node, local, global);
        if(result == -1 && node->child != NULL) {
            annotated_tree(node->child, local, global);
        }
        if(node->brother == NULL)
        	break;
		node = node->brother;
    }
}

int add_type(Node *node, Symbol_Table *local, Symbol_Table *global) {
	//printf("Token: %s, Value: %s\n", node->token, node->value);

    if(strcmp(node->token, "Plus") == 0 || strcmp(node->token, "Minus") == 0 || strcmp(node->token, "Not") == 0) { // Unary
		add_unary_type(node, local, global);
		return 1;
    } else if(strcmp(node->token, "Id") == 0){ // Id
		char *aux = add_id_type(node, local, global);
		if(aux == NULL)
			return -1;
		node->type = strdup(aux);
		return 1;
    } else if(strcmp(node->token, "Call") == 0){ // Call
		add_call_type(node, local, global);
		return 1;
    } else if(strcmp(node->token, "Eq") == 0 || strcmp(node->token, "Ne") == 0 || strcmp(node->token, "Le") == 0 || strcmp(node->token, "Ge") == 0 || strcmp(node->token, "Lt") == 0 || strcmp(node->token, "Gt") == 0 || strcmp(node->token, "And") == 0 || strcmp(node->token, "Or") == 0 || strcmp(node->token, "BitwiseAnd") == 0 || strcmp(node->token, "BitwiseOr") == 0 || strcmp(node->token, "BitwiseXor") == 0) { // Comparisons
		add_comparison_type(node, local, global);
		return 1;
    } else if(strcmp(node->token, "IntLit") == 0 || strcmp(node->token, "ChrLit") == 0 || strcmp(node->token, "RealLit") == 0) { // Literals
		add_literal_type(node, local, global);
		return 1;
    } else if(strcmp(node->token, "Store") == 0 || strcmp(node->token, "Comma") == 0 || strcmp(node->token, "Mul") == 0 || strcmp(node->token, "Div") == 0 || strcmp(node->token, "Mod") == 0  || strcmp(node->token, "Add") == 0 || strcmp(node->token, "Sub") == 0 ){ // Expr
		/* if((strcmp(node->token, "Store") == 0) && (strcmp(node->child->token, "Id") == 0)){
			printf("Line %d, col %d: Lvalue required\n", node->child->line, node->child->column);
		} */
		add_type(node->child, local, global);
        add_type(node->child->brother, local, global);
		char *aux = type_compare(node->child->type, node->child->brother->type, node->token);
		if(aux == NULL)
			return -1;
		node->type = strdup(aux);
		return 1;
    } else if(strcmp(node->token, "Declaration") == 0) {
		add_declaration_types(node, local, global);
		return 1;
	}
	return -1;
}

void add_unary_type(Node *node, Symbol_Table *local, Symbol_Table *global) {
    add_type(node->child, local, global);
	node->type = strdup("int");
	/* if(node->child != NULL && !strcmp(node->child->type, "undef"))
		printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", node->child->line, node->child->column, node->token, node->child->type); */
	
}

void add_comparison_type(Node *node, Symbol_Table *local, Symbol_Table *global) { // Comparison always has 2 children
    add_type(node->child, local, global);
    add_type(node->child->brother, local, global);
	node->type = strdup("int");

	/* if(!strcmp(node->child->type, "undef") || !strcmp(node->child->brother->type, "undef"))
		printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", node->line, node->column, node->token, node->child->type, node->child->brother->type); */
	/*Operator <node->token> cannot be applied to types <node->child->type>, <node->child->brother->type>*/ // SEMANTIC
}

void add_call_type(Node *node, Symbol_Table *local, Symbol_Table *global){
	/* int gotten_params = 0, expected_params = 0; */
    Node *node_aux = node->child->brother; // First param
	/* Param *param = (Param*)malloc(sizeof(param));
	Symbol *symbol_aux = global->symbol;
	while(symbol_aux != NULL){
		if(strcmp(symbol_aux->name, node->child->value) == 0){
			param = symbol_aux->param;
			break;
		}
		symbol_aux = symbol_aux->next;
	}
	while(node_aux != NULL){
		gotten_params++;
		node_aux = node_aux->brother;
	}
	if(param->type != NULL){
		while(param != NULL){
			if(strcmp(param->type, "void") != 0){
				expected_params++;
			}
			if(param->next != NULL){
				param = param->next;
			} else{
				break;
			}
		}
	} */
	node_aux = node->child->brother;
    while(node_aux != NULL){ // Find type of all params
        add_type(node_aux, local, global);
        node_aux = node_aux->brother;
    }
	add_type(node->child, local, global); // Find type of function
	/* if(expected_params == 0){ // SEMANTIC
		printf("Line %d, col %d: Symbol %s is not a function\n", node->child->line, (int)((node->child->column)-strlen(node->child->value)), node->child->value);
	} else if(gotten_params != expected_params){
		printf("Line %d, col %d: Wrong number of arguments to function %s (got %d, required %d)\n", node->child->line, (int)((node->child->column)-strlen(node->child->value)), node->child->value, gotten_params, expected_params);
	} */
    /* char *function_type = add_id_type(node->child, local, global); */
    /* node->type = strdup(function_type); */
}

char* add_id_type(Node *node, Symbol_Table *local, Symbol_Table *global) { // Finds type of x in Id(x)
    //printf("Node Variable: %s %s\n", node->token, node->value);
	Symbol *symbol_aux = local->symbol;
	//printf("Table: %s\n", local->name);
    while(symbol_aux != NULL){
		//printf("Variable(local table): %s\n",symbol_aux->name);
        if(strcmp(symbol_aux->name, node->value)==0) { // Declared in local table
            if(symbol_aux->param != NULL){
                node->param = symbol_aux->param;
                node->function = 1;
            }
            return symbol_aux->type;
        }
        symbol_aux = symbol_aux->next;
    } 
    symbol_aux = global->symbol;
    while(symbol_aux != NULL){
		//printf("Variable(global table): %s\n",symbol_aux->name);
        if(strcmp(symbol_aux->name, node->value)==0) { // Declared in global table
            if(symbol_aux->param != NULL){
                node->param = symbol_aux->param;;
                node->function = 1;
            }
			//printf("symbol: %s, type: %s\n", symbol_aux->name, symbol_aux->type);
            return symbol_aux->type;
        }
		if(symbol_aux->next == NULL)
			break;
        symbol_aux = symbol_aux->next;
    } 
    return "undef"; // symbol doesn't exist => semantic error
}

void add_literal_type(Node *node, Symbol_Table *local, Symbol_Table *global) {
	//printf("Type: %s, Value: %s\n", node->token, node->value);
    if(strcmp(node->token, "RealLit") == 0) { // RealLit
        node->type = strdup("double");
    } else { // ChrLit, IntLit
        node->type = strdup("int");
    }
}

void add_declaration_types(Node *node, Symbol_Table *local, Symbol_Table *global) { // Only adds type to third child
	/* if(strcmp(node->child->token, "Void") == 0){ // SEMANTIC
		printf("Line %d, col %d: Invalid use of void type in declaration\n", node->child->line, node->child->column);
	} */
	if(node->child->brother->brother != NULL){
		add_type(node->child->brother->brother, local, global);
	}
}

char* type_compare(char *ftype, char *stype, char *token) {
	if(ftype == NULL && stype != NULL){
		return stype;
	} else if(ftype != NULL && stype == NULL){
		return ftype;
	} else if(ftype == NULL && stype == NULL){
		return "undef";
	} else if(strcmp(ftype, "undef") == 0 || strcmp(stype, "undef") == 0){
		return "undef";
	}else{
		if(strcmp(token, "Add") == 0 || strcmp(token, "Sub") == 0 || strcmp(token, "Mul") == 0 || strcmp(token, "Div") == 0){
			if(strcmp(ftype, "int") == 0 ) {
				if(strcmp(stype, "int") == 0 || strcmp(stype, "char") == 0) { // int * char, int * int
					return "int";
				} else if(strcmp(stype, "double") == 0){ // int * double
					return "double";
				}
			} else if(strcmp(ftype, "double") == 0) {
				if(strcmp(stype, "double") == 0|| strcmp(stype,"char") == 0|| strcmp(stype,"int") == 0) { // double * double, double * int, double * char
					return "double";
				}
			}
			return "undef";
		} else if(strcmp(token, "Mod") == 0){
			if(strcmp(ftype, "int") == 0 || strcmp(ftype, "short") == 0){
				if(strcmp(stype, "int") == 0 || strcmp(stype, "short") == 0){
					return "int";
				}
			}
			return "undef";
		}else if(strcmp(token, "Comma") == 0) {
			return stype;
		} else if(strcmp(token, "Store") == 0) {
			return ftype;
		}
	}
	return "int";
}