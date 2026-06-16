#ifndef TOKENS_H
#define TOKENS_H

char punctuation[] = {'(', ')', '[', ']', '{', '}', ',', ';', '\0'};

char* keywords[] = {"print\0"};

typedef enum {
  NUMBER,
  OPERATOR,
  PRINT,
  L_PAREN,
  R_PAREN,
  EOF
} TokType;

typedef struct {
  TokType type;
  char* text; // maybe get an actual value for the literal later
  size_t text_len;
  int row;
  int column;
} Token;

#endif



