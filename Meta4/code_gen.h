#include "tree.h"
#ifndef CODE_GEN_H
#define CODE_GEN_H

int temporary_var;
char* types_to_llvm(char* type);
void code_gen(Node *node);
void program_gen(Node *node);
void declaration_gen(Node* node);
void func_definition_gen(Node *node);
void params_gen(Node *node);
void func_body_gen(Node *node);
void chrlit_gen(Node *node);
void intlit_gen(Node *node);
void reallit_gen(Node *node);
void id_gen(Node *node);
void store_gen(Node *node);
void minus_gen(Node *node);
void call_gen(Node *node);
void return_gen(Node *node);
void add_gen(Node *node);
void sub_gen(Node *node);
void mul_gen(Node *node);
void div_gen(Node *node);
void mod_gen(Node *node);
int is_global(char *name);
void convert_types(Node *param, char *expected);
#endif //CODE_GEN_H
