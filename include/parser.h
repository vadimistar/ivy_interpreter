#ifndef IVY_PARSER_H
#define IVY_PARSER_H

#include "list.h"
#include "lexer.h"
#include "ast.h"

typedef struct {
  ivy_list tokens;
  size_t index;
} parser;

parser parser_init(lexer t_lexer); 
token *parser_peek(parser *prs, size_t offset);
token *parser_curr(parser *prs);
void parser_move(parser *prs);
token *parser_next(parser *prs);

void parser_free(parser *prs);

ast_node *parser_parse_expr(parser *prs);
ast_node *parser_parse_integer(parser *prs);
ast_node *parser_parse_binary_op(parser *prs);
ast_node *parser_parse_unary_op(parser *prs);

#endif//IVY_PARSER_H
