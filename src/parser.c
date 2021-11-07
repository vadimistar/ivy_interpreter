#include "../include/parser.h"
#include <assert.h>

parser parser_init(lexer t_lexer) {
  parser t_parser = (parser) {
    .tokens = ivy_list_init(sizeof(token)),
    .index = 0,
  }; 
  while (lexer_not_end_of_line(&t_lexer)) {
    token t_token = lexer_get_token(&t_lexer); 
    ivy_list_push(&t_parser.tokens, &t_token);
    token_free(&t_token);
  }
  return t_parser;
}

token *parser_peek(parser *prs, size_t offset) {
  assert(offset < prs->tokens.size && "Token out of bounds"); 
  return ivy_list_get(&prs->tokens, prs->index + offset); 
}

token *parser_curr(parser *prs) {
  return parser_peek(prs, 0);
}

void parser_move(parser *prs) {
  if (prs->index != prs->tokens.size) {
    ++prs->index;
  }
}

token *parser_next(parser *prs) {
  parser_move(prs);
  return parser_curr(prs);
}

void parser_free(parser *prs) {
  ivy_list_free(&prs->tokens);
}
