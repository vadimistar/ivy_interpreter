#include "../include/lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

const char *token_kind_as_str(token_kind kind) {
  switch (kind) {
  case TOKEN_EOF:
    return "end of file";
  case TOKEN_PLUS:
    return "'+'";
  case TOKEN_MINUS:
    return "'-'";
  case TOKEN_INTEGER:
    return "integer";
  case TOKEN_WORD:
    return "word";
  default:
    assert(0 && "token kind is not handled");
  }
}

void token_free(token *t) {
  if (t->value != NULL) {
    free(t->value);
  }
}

const char *token_value(token *t) {
  if (t->value != NULL) {
    return t->value;
  }
  return "(null)";
}

lexer lexer_init(char *raw) {
  return (lexer) { .curr = raw, .loc = 1, };
}

void lexer_adv(lexer *l) {
  if (*l->curr == '\0') { return; }
  ++l->curr;
  ++l->loc;
}

token lexer_get_number(lexer *l) {
  char *start = l->curr;
  size_t size = 0;
  for (; *l->curr != '\0' && isdigit(*l->curr); lexer_adv(l)) {
    ++size;
  }
  char *val = malloc((size + 1) * sizeof(char));
  strncpy(val, start, size);
  val[size] = '\0';

  return (token) {
    .kind = TOKEN_INTEGER,
    .value = val,
  };
}

token lexer_get_word(lexer *l) {
  char *start = l->curr;
  size_t size = 0;
  for (; *l->curr != '\0' && (isalnum(*l->curr) || *l->curr == '_');
       lexer_adv(l)) {
    ++size;
  }
  char *val = malloc((size + 1) * sizeof(char));
  strncpy(val, start, size);
  val[size] = '\0';

  return (token) {
    .kind = TOKEN_WORD,
    .value = val,
  };
}

token lexer_get_custom(lexer *l, token_kind t_kind) {
  lexer_adv(l);
  return (token) { .kind = t_kind, .value = NULL, };
}

token lexer_get_token(lexer *l) {
begin:
  switch (*l->curr) {
  case '\0':
    break;
  case ' ':
  case '\t':
  case '\n':
    lexer_adv(l);
    goto begin;
  case '+':
    return lexer_get_custom(l, TOKEN_PLUS);
  case '-':
    return lexer_get_custom(l, TOKEN_MINUS);
  default:
    if (isdigit(*l->curr)) {
      return lexer_get_number(l);
    }
    if (isalpha(*l->curr)) {
      return lexer_get_word(l);
    }
    fprintf(stderr, "%lu: ERROR: Unknown character: %c\n",
        l->loc, *l->curr);
    exit(1);
  }
  return (token) {
    .kind = TOKEN_EOF,
    .value = NULL,
  };
}

int lexer_not_end_of_line(lexer *l) {
  return *(l->curr) != '\n';
}
