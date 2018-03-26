//
// Created by Ruben Leal on 24/03/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* create_tree(char* token){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->child = NULL;
    tmp->brother = NULL;
    tmp->token = (char*) malloc(sizeof(token)* sizeof(char));
    strcpy(tmp->token, token);

    return tmp;

}

void insert_child(Node **node, char* token) {
    if(*node == NULL)
        return;

    if((*node)->child == NULL){
        (*node)->child = (Node*) malloc(sizeof(Node));

        (*node)->child->child = NULL;
        (*node)->child->brother = NULL;
        (*node)->child->token = (char*) malloc(sizeof(token)* sizeof(char));
        strcpy((*node)->child->token, token);
    }
}

Node* insert_brother(Node **node, char* token) {
    if(*node == NULL)
        return NULL;
    Node *tmp, *prev;
    prev = (*node);
    tmp = (*node)->brother;

    while (tmp != NULL){
        prev = tmp;
        tmp = tmp->brother;
    }
    prev->brother = (Node*) malloc(sizeof(Node));
    prev->brother->child = NULL;
    prev->brother->brother = NULL;
    prev->brother->token = (char*) malloc(sizeof(token)*sizeof(char));
    strcpy(prev->brother->token, token);
    return prev->brother;
}

void print_tree(Node *root, int dots){
    if(root == NULL)
        return;
    for (int i = 0; i < dots; ++i) {
        printf("..");
    }
    //Colocar de acordo com o enunciado
    printf("%s\n", root->token);

    print_tree(root->child, dots+1);
    print_tree(root->brother, dots);
}

void clear(Node *root){
    if(root != NULL) {
        clear(root->child);
        clear(root->brother);
        free(root->token);
        free(root);
        
    }
}

int main(){

    Node* tree = create_tree("1");

    insert_child(&tree, "1.1");

    insert_brother(&(tree->child), "1.2");
    insert_brother(&(tree->child), "1.3");


    insert_child(&(tree->child), "1.1.1");

    insert_brother(&(tree->child->child), "1.1.2");
    insert_brother(&(tree->child->child), "1.1.3");
    print_tree(tree, 0);
    printf("\n\n");
    clear(tree);
    print_tree(tree, 0);

}