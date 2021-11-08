#include "../include/eval.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void stop_eval() {
  fprintf(stderr, "%s", "Process is interrupted due to previous errors.\n");
  exit(1);
}

ivy_value eval_expr(ast_node *node) {
  if (node == NULL) { stop_eval(); }
  switch (node->kind) {
    case BINARY_OP_AST:
      return eval_binary_expr(node);   
    case INTEGER_AST:
      return eval_integer_ast(node);
    default:
      assert(0 && "node kind is not handled");
  }
}

ivy_value eval_binary_expr(ast_node *node) {
  if (node == NULL) { stop_eval(); }
  ivy_value lhs = eval_unary_expr(node->left);    
  ivy_value rhs = eval_unary_expr(node->right);    
  switch (node->operand) {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
      if (lhs.kind != rhs.kind) {
        fprintf(stderr, "%lu: ERROR: Expressions don't have the same type.",
            node->loc); 
        exit(1);
      }
      switch (lhs.kind) {
        case IVY_VALUE_INT:
          return (ivy_value){
            .as_int = lhs.as_int + rhs.as_int,
            .kind = IVY_VALUE_INT,
          };
          break;
        case IVY_VALUE_FLOAT:
          return (ivy_value){
            .as_float = lhs.as_float + rhs.as_float,
            .kind = IVY_VALUE_FLOAT,
          };
        default:
          assert(0 && "This kind of value is not handled");
      }
      break;
    default:
      fprintf(stderr, "%lu: ERROR: Invalid operand", node->loc);  
      exit(1);
  }
}

ivy_value eval_unary_expr(ast_node *node) {
  if (node == NULL) { stop_eval(); }
  switch (node->kind) {
    case INTEGER_AST:
      return eval_integer_ast(node);
    default:
      assert(0 && "node kind is not handled");
  }
}

ivy_value ivy_str_to_int(char *val) {
  printf("Input: %s\n", val);
  char *end;
  unsigned long res = strtoull(val, &end, 10);
  if (strcmp(end, "\0") == 0) {
    return (ivy_value) {
      .as_int = res,
      .kind = IVY_VALUE_INT,
    };
  }
  return (ivy_value) {
    .kind = IVY_VALUE_NULL, 
  };
}

ivy_value eval_integer_ast(ast_node *node) { 
  if (node == NULL) { stop_eval(); }
  assert(node->value != NULL);
  return ivy_str_to_int(node->value);
}
