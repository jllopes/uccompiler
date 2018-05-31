#include "tree.h"
#ifndef CODE_GEN_H
#define CODE_GEN_H

int temporary_var;
int and_cmp;
int or_cmp;
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
void or_gen(Node *node);
void and_gen(Node *node);
void bitwiseand_gen(Node *node);
void bitwiseor_gen(Node *node);
void bitwisexor_gen(Node *node);
void eq_gen(Node *node);
void ne_gen(Node *node);
void le_gen(Node *node);
void ge_gen(Node *node);
void lt_gen(Node *node);
void gt_gen(Node *node);
void not_gen(Node *node);
int is_global(char *name);
int is_expression(Node *node);
int greater_type(char *first, char *second);
void convert_types(Node *param, char *expected);
#endif //CODE_GEN_H
