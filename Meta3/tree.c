#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* create_node(char* token, char* value){ /* Creates n0d3 */
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->child = NULL; 
    tmp->brother = NULL; 
    tmp->token = (char*) malloc(sizeof(token)* sizeof(char));
    tmp->param = NULL;
    tmp->type = NULL;
    tmp->function = 0;
    strcpy(tmp->token, token);
    if(value != NULL){
        tmp->value = (char*) malloc(sizeof(value)* sizeof(char));
        strcpy(tmp->value, value);
    } else {
        tmp->value = NULL;
    }
    return tmp; /* returns n0d3 */
}

Token* create_token(int line, int column, char *id){ /* Create token to return from lex */
    Token* token = (Token*)malloc(sizeof(Token));
    token->line = line;
    token->column = column;
    token->id = strdup(id);
    return token;
}

void insert_first_child(Node *node, Node *child_node) { /* child_node = typespec */
    if(child_node == NULL) /* If node to insert is null end function */
        return;

    Node *tmp = (Node*) malloc(sizeof(Node));
    Node *uncle = node->brother;
    if(node->child == NULL){ /* If node has no child, create one */
        node->child = (Node*) malloc(sizeof(Node));
        node->child = child_node;
    } else {
        tmp = node->child;
        node->child = child_node;
        node->child->brother = tmp;
    }
    while(uncle != NULL){ /* Goes through cousins to add type spec */
        tmp = uncle->child;
        uncle->child = create_node(child_node->token, NULL);
        uncle->child->brother = tmp;
        uncle = uncle->brother;
    }
}

Node* insert_child(Node *node, Node *child_node) {
    if(node == NULL) /* If node to insert is null end function */
        return NULL;
    if(node->child == NULL){ /* If node has no child, create one */
        node->child = (Node*) malloc(sizeof(Node));
        node->child = child_node;
    } else {
        Node *tmp = (Node*) malloc(sizeof(Node));
        Node *prev = (Node*) malloc(sizeof(Node));
        prev = node->child;
        tmp = node->child->brother;
        while (tmp != NULL){ /* Goes through all the brothers */
            prev = tmp;
            tmp = tmp->brother;
        }
        prev->brother = (Node*) malloc(sizeof(Node));
        prev->brother=child_node;
    }
    return node;
}

Node* insert_brother(Node *node, Node *brother_node) {
    if(node == NULL) /* If node to insert is null end function */
        return NULL;
    Node *tmp = (Node*) malloc(sizeof(Node));
        Node *prev = (Node*) malloc(sizeof(Node));
    prev = node;
    tmp = node->brother;

    while (tmp != NULL){ /* Goes through all the brothers */
        prev = tmp;
        tmp = tmp->brother;
    }
    prev->brother = (Node*) malloc(sizeof(Node));
    prev->brother=brother_node;
    return node;
}

void print_child_brother(Node *node){
    printf("brother_node->token: %s; brother_node->value: %s\n", node->brother->token, node->brother->value);
    printf("node->child->token: %s; node->child->value: %s\n", node->child->token, node->child->value);
}

void print_tree(Node *node, int dots){
    if(node == NULL)
        return;
    for (int i = 0; i < dots; ++i) {
        printf("..");
    }
    if(node->value != NULL){
        printf("%s(%s)\n", node->token, node->value);
    } else{
        printf("%s\n", node->token);
    }

    if(node->child != NULL)
        print_tree(node->child, dots+1);
    if(node->brother != NULL)
        print_tree(node->brother, dots);
}

void print_annotated_tree(Node *node, int dots){
    //printf("Token: %s, Value: %s, Type: %s\n", node->token, node->value, node->type);
    if(node == NULL)
        return;
    for (int i = 0; i < dots; ++i) {
        printf("..");
    }
    if(node->value != NULL){
        printf("%s(%s)", node->token, node->value);
        if(node->type != NULL){
            printf(" - %s", node->type);
            if(node->function != 0){
                Param *aux = node->param;
                if(aux != NULL){
                    printf("(%s", aux->type);
                    aux = aux->next;
                    while(aux != NULL){
                        printf(",%s", aux->type);
                        aux = aux->next;
                    }
                    printf(")");
                }
            }
        }
        printf("\n");
    } else{
        printf("%s", node->token);
        if(node->type != NULL){
            printf(" - %s", node->type);
            if(node->function != 0){
                Param *aux = node->param;
                if(aux != NULL){
                    printf("(%s", aux->type);
                    aux = aux->next;
                    while(aux != NULL){
                        printf(",%s", aux->type);
                        aux = aux->next;
                    }
                    printf(")");
                }
            }
        }
        printf("\n");
    }

    if(node->child != NULL)
        print_annotated_tree(node->child, dots+1);
    if(node->brother != NULL)
        print_annotated_tree(node->brother, dots);
}
void clear(Node *node){ /* Free node memory */
    if(node != NULL) {
        clear(node->child);
        clear(node->brother);
        free(node->token);
        free(node);   
    }
}