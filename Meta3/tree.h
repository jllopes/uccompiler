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
Node* create_node(char* token, char* value);
void insert_first_child(Node *node, Node *child_node);
Node* insert_child(Node *node, Node *child_node);
Node* insert_brother(Node *node, Node *brother_node);
void print_tree(Node *root, int dots);
void clear(Node *root);


#endif //TREE_H
