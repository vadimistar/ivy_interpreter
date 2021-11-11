#ifndef IVY_AST_H
#define IVY_AST_H
#include "lexer.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct ast_node ast_node;

typedef enum {
  NULL_AST,
  INTEGER_AST,
  PAREN_EXPR_AST,
  BINARY_EXPR_AST,
  UNARY_EXPR_AST,
} ast_kind;

struct ast_node {
  char *value; // integer_ast
  token_kind operand; // binary_expr_ast / unary_expr_ast
  ast_node *left;
  ast_node *right;
  ast_node *child;
  ast_kind kind;
  size_t loc;
}; 

ast_node *null_ast_init();
ast_node *ast_init(ast_kind kind);

ast_node *integer_ast_init(char *val);

void ast_free(ast_node *node);

bool is_binary_op(token_kind kind);

#endif//IVY_AST_H
