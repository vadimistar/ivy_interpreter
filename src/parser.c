#include "../include/parser.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

parser parser_init(lexer t_lexer) {
  parser t_parser = (parser) {
    .tokens = ivy_list_init(sizeof(token)),
    .index = 0,
  }; 
  while (lexer_not_end_of_line(&t_lexer)) {
    token t_token = lexer_get_token(&t_lexer); 
    ivy_list_push(&t_parser.tokens, &t_token);
  }
  token t_eof = (token) {
    .kind = TOKEN_EOF,
    .value = NULL,
    .loc = t_lexer.loc,
  };
  ivy_list_push(&t_parser.tokens, &t_eof); 
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
  for (size_t i = 0; i != prs->tokens.size; ++ i) {
    token_free(ivy_list_get(&prs->tokens, i));  
  }
  ivy_list_free(&prs->tokens);
}

size_t parser_left(parser *prs) {
  return prs->tokens.size - prs->index; 
}

bool parser_match(parser *prs, token_kind t_kind) {
  if (parser_curr(prs)->kind != t_kind) {
    fprintf(stderr, "%lu: ERROR: Expected %s, but got %s\n", parser_curr(prs)->loc, token_kind_as_str(t_kind), token_kind_as_str(parser_curr(prs)->kind));
    while (parser_curr(prs) != TOKEN_EOF) {
      parser_move(prs); 
    }
    return false;  
  }
  parser_move(prs); 
  return true;
}

ast_node *parser_parse_expr(parser *prs) {
  switch (parser_left(prs)) {
    case 1:
      fprintf(stderr, "%lu: ERROR: Got null expr\n", parser_curr(prs)->loc);
      return NULL;
    default:
      break;
  }
  switch (parser_curr(prs)->kind) {
    case TOKEN_INTEGER:
      //if (parser_left(prs) > 2 && is_binary_op(parser_peek(prs, 1)->kind)) {
      //  return parser_parse_binary_op(prs);
      //}
      return parser_parse_integer(prs);
    case TOKEN_LPAREN:
      return parser_parse_paren_expr(prs);
    case TOKEN_PLUS:
    case TOKEN_MINUS:
      return parser_parse_unary_op(prs);
    default:
      fprintf(stderr, "%lu: ERROR: Unknown expression", parser_curr(prs)->loc);
      return NULL;
  }
}

ast_node *parser_parse_integer(parser *prs) {
  if (parser_curr(prs)->kind == TOKEN_INTEGER) {
    char *val = parser_curr(prs)->value;
    parser_move(prs);
    return integer_ast_init(val);
  }
  fprintf(stderr, "%lu: ERROR: Expected integer, but got %s\n", 
      parser_curr(prs)->loc, token_kind_as_str(parser_curr(prs)->kind));
  return NULL;    
}

ast_node *parser_parse_unary_op(parser *prs) {
  switch (parser_curr(prs)->kind) {
    case TOKEN_PLUS:
    case TOKEN_MINUS: {
      ast_node *t_node = ast_init(UNARY_EXPR_AST); 
      t_node->operand = parser_curr(prs)->kind;
      parser_move(prs);
      t_node->child = parser_parse_expr(prs);
      return t_node;
    }
    default:
      fprintf(stderr, "%lu: ERROR: Invalid unary expression: %s", 
        parser_curr(prs)->loc, token_kind_as_str(parser_curr(prs)->kind));     
      return NULL;
  }
}

ast_node *parser_parse_binary_op(parser *prs) {
  ast_node *t_left = parser_parse_unary_op(prs);
  if (t_left == NULL) {
    return NULL; 
  }
  token_kind t_kind = parser_curr(prs)->kind;
  parser_move(prs);
  switch (t_kind) {
    case TOKEN_PLUS:
    case TOKEN_MINUS: {
      ast_node *t_right = parser_parse_unary_op(prs);  
      if (t_right == NULL) {
        return NULL;
      }
      ast_node *t_expr = ast_init(BINARY_EXPR_AST);
      t_expr->left = t_left;
      t_expr->operand = t_kind;
      t_expr->right = t_right;
      parser_move(prs);
      return t_expr;
    }
    default:
      fprintf(stderr, "%lu: ERROR: Expected valid binary operator, but got %s\n",
          parser_curr(prs)->loc, token_kind_as_str(parser_curr(prs)->kind));
  }
  parser_move(prs);
  return NULL;
}

ast_node *parser_parse_paren_expr(parser *prs) {
  if (!parser_match(prs, TOKEN_LPAREN)) { return NULL; }
  ast_node *t_expr = parser_parse_expr(prs);  
  if (!parser_match(prs, TOKEN_RPAREN)) { return NULL; }
  return t_expr;
}
