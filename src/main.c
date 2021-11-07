#include "../include/lexer.h"
#include "../include/parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void evaluate(char *input) {
  lexer t_lexer = lexer_init(input);  
  parser t_parser = parser_init(t_lexer);
  ast_node *t_expr = parser_parse_expr(&t_parser); 
  if (t_expr != NULL) { ast_free(t_expr); }
   
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
