//
// Created by Ruben Leal on 24/03/2018.
//

#ifndef NTREE_TREE_H
#define NTREE_TREE_H

typedef struct Node Node;

struct Node{
    char *token;
    Node *child;
    Node *brother;
};

Node* create_tree(char* token);
void insert_child(Node **node, char* token);
Node* insert_brother(Node **node, char* token);
void print_tree(Node *root, int dots);
void clear(Node *root);


#endif //NTREE_TREE_H
