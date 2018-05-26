void func_declaration_gen(Node *node){
	char *type = types_to_llvm(node->child->token);
	char *name = node->child->brother->value; /* Value from ID */
	Node *aux = node->child->brother->brother->child; /* Skips until first ParamDeclaration */
	params_gen(aux);
	printf("")
}