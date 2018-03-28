#ifndef TREE_H
#define TREE_H

typedef struct Node Node;

struct Node{
    char *token;
    char *value;
    Node *child;
    Node *brother;
};

Node* root;
Node* create_tree();
void insert_child(Node **node, char* token);
Node* insert_brother(Node **node, char* token);
void print_tree(Node *root, int dots);
void clear(Node *root);


#endif //TREE_H
