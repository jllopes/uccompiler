#ifndef TREE_H
#define TREE_H

typedef struct Node Node;
typedef struct Token Token;

struct Node{
    char *token;
    char *value;
    Node *child;
    Node *brother;
};

struct Token{
	int line;
	int column;
	char *id;
};

Node* root;
Node* create_node(char* token, char* value);
Token* create_token(int line, int column, char *id); /* Create token to return from lex */
void insert_first_child(Node *node, Node *child_node);
Node* insert_child(Node *node, Node *child_node);
Node* insert_brother(Node *node, Node *brother_node);
void print_tree(Node *root, int dots);
void clear(Node *root);


#endif //TREE_H
