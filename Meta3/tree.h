#ifndef TREE_H
#define TREE_H

typedef struct Node Node;
typedef struct Param Param;
typedef struct Token Token;

struct Node{
    char *token;
    char *value;
    Param *param;
    char *type;
    int function;
    int line;
    int column;
    Node *child;
    Node *brother;
};

struct Token{
	int line;
	int column;
	char *id;
};

struct Param{
	char *name;
	char *type;
	Param *next;
};

Node* root;
Node* create_node(char* token, char* value, int line, int col);
Token* create_token(int line, int column, char *id); /* Create token to return from lex */
void insert_first_child(Node *node, Node *child_node);
Node* insert_child(Node *node, Node *child_node);
Node* insert_brother(Node *node, Node *brother_node);
void print_tree(Node *root, int dots);
void print_annotated_tree(Node *node, int dots);
void clear(Node *root);


#endif //TREE_H
