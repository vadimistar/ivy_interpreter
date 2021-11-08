#include "../include/ast.h"

ast_node *null_ast_init() {
  ast_node *node = (ast_node *) calloc(1, sizeof(ast_node));
  return node;
}

ast_node *ast_init(ast_kind kind) {
  ast_node *node = (ast_node *) calloc(1, sizeof(ast_node));
  node->kind = kind;
  return node;
}

ast_node *integer_ast_init(char *val) {
  ast_node *node = ast_init(INTEGER_AST);
  node->value = val;
  return node;
}

void ast_free(ast_node *node) {
  if (node->left != NULL) {
    ast_free(node->left); 
  }
  if (node->right != NULL) {
    ast_free(node->right); 
  }
  free(node);
}
