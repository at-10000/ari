#include <stddef.h>

#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
  NUMBER,
  STR_LIT,
  IDENTIFIER,

  OPERATOR,
  ADD_OP,
  SUB_OP,
  MUL_OP,
  DIV_OP,
  EQL_OP,

  IS_EQUAL,
  LARGER_THAN,
  SMALLER_THAN,
  LARGER_OR_EQUAL,
  SMALLER_OR_EQUAL,

  PRINT,

  L_PAREN,
  R_PAREN,
  SEMICOLON,
  
  END_OF_FILE,
  NONE
} TokType;

typedef struct {
  TokType type;
  char* text; // maybe get an actual value for the literal later
  size_t text_len;
  // long 
  double num_val;
  // bool is_num;
  int line;
  int column;
} Token;

Token nextTok (char* text, unsigned int* start, size_t size);

void printTok (Token tok);

#endif


