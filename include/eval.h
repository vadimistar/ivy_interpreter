#ifndef IVY_EVAL_H
#define IVY_EVAL_H

#include <stdbool.h>
#include "ast.h"

typedef enum {
  IVY_VALUE_NULL,
  IVY_VALUE_INT,
  IVY_VALUE_FLOAT,
} ivy_value_kind;

typedef struct { 
  union {
    long as_int;
    double as_float;
  };
  ivy_value_kind kind; 
} ivy_value;

void stop_eval();

ivy_value eval_expr(ast_node *node);
ivy_value eval_binary_expr(ast_node *node);
ivy_value eval_unary_expr(ast_node *node);

bool ivy_values_check_types(ivy_value lhs, ivy_value rhs, loc_t loc);
ivy_value ivy_value_int_init(long val);
ivy_value ivy_value_float_init(double val);

ivy_value ivy_str_to_int(char *val);
ivy_value eval_integer_ast(ast_node *node);

#endif//IVY_EVAL_H
