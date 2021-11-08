#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/eval.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void evaluate(char *input) {
  lexer t_lexer = lexer_init(input);  
  parser t_parser = parser_init(t_lexer);
  ast_node *t_expr = parser_parse_expr(&t_parser);
  if (t_expr != NULL) { 
    ivy_value t_val = eval_expr(t_expr); 
    switch (t_val.kind) {
      case IVY_VALUE_INT:
        printf("Output: %lu\n", t_val.as_int);
        break;
      case IVY_VALUE_FLOAT:
        printf("Output: %f\n", t_val.as_float); 
        break;
      default:
        assert(0 && "this kind is not handled");
    }
    ast_free(t_expr); 
  }
  parser_free(&t_parser);
}

int main() {
  puts( "Ivy (version 0.1)\n" 
        "Type 'q' for quit\n"); 
  while (1) {
    printf("> ");
    fflush(stdout);
    char *inp = malloc(256 * sizeof(char));
    fgets(inp, 256 * sizeof(char), stdin);
    if (strcmp(inp, "q\n") == 0) {
      free(inp);
      break;
    }
    evaluate(inp);
    free(inp);
  }
  return 0;
}
