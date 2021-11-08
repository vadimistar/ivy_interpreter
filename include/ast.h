#ifndef IVY_AST_H
#define IVY_AST_H
#include "lexer.h"

#include <stdlib.h>

typedef struct ast_node ast_node;

typedef enum {
  NULL_AST,
  INTEGER_AST,
  BINARY_OP_AST,
} ast_kind;

struct ast_node {
  char *value; // integer_ast
  token_kind operand; // binary_op_ast
  ast_node *left;
  ast_node *right;
  ast_kind kind;
  size_t loc;
}; 

ast_node *null_ast_init();
ast_node *ast_init(ast_kind kind);

ast_node *integer_ast_init(char *val);

void ast_free(ast_node *node);


#endif//IVY_AST_H
