#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* create_node(char* token, char* value){ /* Creates n0d3 */
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->child = NULL; 
    tmp->brother = NULL; 
    tmp->token = (char*) malloc(sizeof(token)* sizeof(char));
    strcpy(tmp->token, token);
    if(value != NULL){
        tmp->value = (char*) malloc(sizeof(value)* sizeof(char));
        strcpy(tmp->value, value);
    } else {
        tmp->value = NULL;
    }
    return tmp; /* returns n0d3 */
}

Node* insert_child(Node *node, Node *child_node) {
    //printf("child_node->token: %s;\n", child_node->token);
    if(node == NULL) /* If node to insert is null end function */
        return NULL;

    if(node->child == NULL){ /* If node has no child, create one */
        node->child = (Node*) malloc(sizeof(Node));
        /*node->child->child = NULL;
        node->child->brother = NULL;
        node->child->token = NULL;*/
        node->child = child_node;
    } else {
        Node *tmp, *prev;
        prev = node->child;
        tmp = node->child->brother;

        while (tmp != NULL){ /* Goes through all the brothers */
            prev = tmp;
            tmp = tmp->brother;
        }
        prev->brother = (Node*) malloc(sizeof(Node));
        /*prev->brother->child = NULL;
        prev->brother->brother = NULL;
        prev->brother->token = NULL;*/
        prev->brother=child_node;
    }
    return node;
}

Node* insert_brother(Node *node, Node *brother_node) {
    //printf("brother_node->token: %s;\n", brother_node->token);
    //printf("node->token: %s;\n", node->token);
    if(node == NULL) /* If node to insert is null end function */
        return NULL;
    Node *tmp, *prev;
    prev = node;
    tmp = node->brother;

    while (tmp != NULL){ /* Goes through all the brothers */
        prev = tmp;
        tmp = tmp->brother;
    }
    prev->brother = (Node*) malloc(sizeof(Node));
    /*prev->brother->child = NULL;
    prev->brother->brother = NULL;
    prev->brother->token = NULL;*/
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
    //Colocar de acordo com o enunciado
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

void clear(Node *node){ /* Free node memory */
    if(node != NULL) {
        clear(node->child);
        clear(node->brother);
        free(node->token);
        free(node);   
    }
}

/*int main(){

    Node* tree = create_tree("1");

    insert_child(&tree, "1.1");

    insert_brother(&(tree->child), "1.2");
    insert_brother(&(tree->child), "1.3");


    insert_child(&(tree->child), "1.1.1");

    insert_brother(&(tree->child->child), "1.1.2");
    insert_brother(&(tree->child->child), "1.1.3");
    print_tree(tree, 0);

}*/