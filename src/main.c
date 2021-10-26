#include "../include/lexer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void evaluate(char *input) {
  lexer t_lexer = lexer_init(input);  
  while (*t_lexer.curr != '\n') {
    token t_token = lexer_get_token(&t_lexer); 
    printf("%s\t%s\n", token_kind_as_str(t_token.kind), token_value(&t_token));        
    token_free(&t_token);    
  }
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
