#ifndef IVY_LEXER_H
#define IVY_LEXER_H

#include <stddef.h>

typedef size_t loc_t;

typedef enum {
  TOKEN_EOF,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_INTEGER,
  TOKEN_WORD,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
} token_kind;

typedef struct {
  token_kind kind;
  char *value; 
  loc_t loc;
} token;

const char *token_kind_as_str(token_kind kind);
void token_free(token *t);
const char *token_value(token *t);

typedef struct {
  char* curr; 
  loc_t loc;
} lexer;

lexer lexer_init(char *raw);
void lexer_adv(lexer *l);

token lexer_get_number(lexer *l);
token lexer_get_word(lexer *l);
token lexer_get_custom(lexer *l, token_kind t_kind);

token lexer_get_token(lexer *l);
int lexer_not_end_of_line(lexer *l);

#endif//IVY_LEXER_H
