#include "tree.h"
#ifndef CODE_GEN_H
#define CODE_GEN_H

int temporary_var;
char* types_to_llvm(char* type);
void code_gen(Node *node, char *function);
void program_gen(Node *node, char *function);
void declaration_gen(Node* node, char *function);
void func_definition_gen(Node *node, char *function);
void params_gen(Node *node, char *function);
void func_body_gen(Node *node, char *function);
void chrlit_gen(Node *node, char *function);
void intlit_gen(Node *node, char *function);
void reallit_gen(Node *node, char *function);
void store_gen(Node *node, char *function);
void minus_gen(Node *node, char *function);
void call_gen(Node *node, char *function);
void return_gen(Node *node, char *function);
#endif //CODE_GEN_H
