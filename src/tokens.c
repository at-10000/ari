#include "tokens.h"

#include "dynarr.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char punctuation[] = {'(', ')', '[', ']', '{', '}', ',', ';', '\0'}; // you should probably add '!' among these at some point
char whitespace[] = {' ', '\t', '\n', '\r', '\0'};
char operators[] = {'+', '-', '*', '/', '=', '\0'};

// short int compare_arr_size = 6;
// char* compare[] = {"==\0", "<=\0", ">=\0", "!=\0", "<\0", ">\0"};

char* keywords[] = {"print\0"};
// char* tokTypes[] = {"NUMBER\0", "STR_LIT\0", "IDENTIFIER\0", "OPERATOR\0", "PRINT\0", "L_PAREN\0", "R_PAREN\0", "SEMICOLON\0", "END_OF_FILE\0", "NONE\0"};
// REMEMBER TO CHANGE THE DAMN TOKEN TYPES ARRAY WHEN YOU CHANGE THEM IN THE ENUM

char* tokTypes[] = {
  "NUMBER", "STR_LIT", "IDENTIFIER",
  "OPERATOR", "ADD_OP", "SUB_OP", "MUL_OP", "DIV_OP", "EQL_OP",
  "IS_EQUAL", "LARGER_THAN", "SMALLER_THAN", "LARGER_OR_EQUAL", "SMALLER_OR_EQUAL",
  "PRINT",
  "L_PAREN", "R_PAREN", "SEMICOLON",
  "END_OF_FILE", "NONE"
};

static unsigned int line = 0;
static unsigned int column = 0;

void printTok (Token tok) {
  printf("{type: ");
  
  for (int i = 0; tokTypes[tok.type][i] != '\0'; i ++) {
    printf("%c", tokTypes[tok.type][i]);
  }

  if (tok.type == END_OF_FILE) {
    printf("}");
    return;
  }
  
  printf(", text: \"");
  
  for (int i = 0; tok.text[i] != '\0'; i ++) {
    printf("%c", tok.text[i]);
  }
  printf("\", text_len: %zu, ", tok.text_len);
  
  if (tok.type == NUMBER) {
    printf("num_val: %f, ", tok.num_val);
  }

  printf("line: %d, column: %d}", tok.line, tok.column);
}

bool isPunct (char c) {
  size_t i = 0;
  while (punctuation[i] != '\0') {
    if (punctuation[i] == c) {
      return true;
    }
    i ++;
  }
  return false;
}

TokType classifyPunct(char c) {
  switch (c) {
    case '(':
      return L_PAREN;
    
    case ')':
      return R_PAREN;

    case ';':
      return SEMICOLON;

    default:
      return NONE;
  } // finish this function for other punctuation
}

bool isWhitespace (char c) {
  size_t i = 0;
  while (whitespace[i] != '\0') {
    if (whitespace[i] == c) {
      return true;
    }
    i ++;
  }
  return false;
}

bool isOperator (char c) {
  size_t i = 0;
  while (operators[i] != '\0') {
    if (operators[i] == c) {
      return true;
    }
    i ++;
  }
  return false;
}

TokType classifyOperator (char c) {
  switch (c) {
    case '+':
      return ADD_OP;
    case '-':
      return SUB_OP;
    case '*':
      return MUL_OP;
    case '/':
      return DIV_OP;
    case '=':
      return EQL_OP;
    default:
      return NONE;
  }
}

TokType classifyCompare (char c1, char c2) {
  if (c2 != '=') {
    switch (c1) {
      case '<':
        return SMALLER_THAN;
      case '>':
        return LARGER_THAN;
      default:
        return NONE;
    }
  }
  else {
    switch (c1) {
      case '=':
        return IS_EQUAL;
      case '<':
        return SMALLER_OR_EQUAL;
      case '>':
        return LARGER_OR_EQUAL;
      default:
        return NONE;
    }
  }
}

bool canBeIdentifier (char c) {
  if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_') {
    return true;
  }
  else {
    return false;
  }
}

bool sameType (bool isNumber, char c) {
  if (isNumber) {
    if (('0' <= c && c <= '9') || c == '.') {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (canBeIdentifier(c)) {
      return true;
    }
    else {
      return false;
    }
  }
}

Token nextTok (char* text, unsigned int* start, size_t size) {
  // printf("Inside nextTok\n");

  unsigned int i = *start;

  while (i < size && isWhitespace(text[i])) {
    if (text[i] == '\n') {
      line ++;
      column = 0;
    }
    i ++;
    column ++;
  }

  if (i >= size) {
    Token result;
    result.type = END_OF_FILE;
    *start = i;

    return result;
  }
  
  {
    TokType type = classifyCompare(text[i], text[i + 1]);
    if (type != NONE) {
      Token tok;
      tok.type = type;
      tok.line = line;
      tok.column = column;

      if (type == LARGER_THAN || type == SMALLER_THAN){
        tok.text = malloc(2 * sizeof(char));
        tok.text[0] = text[i];
        tok.text[1] = '\0';
        tok.text_len = 1;
        *start = i + 1;
      }
      else {
        tok.text = malloc(3 * sizeof(char));
        tok.text[0] = text[i];
        tok.text[1] = text[i + 1];
        tok.text[2] = '\0';
        tok.text_len = 2;
        *start = i + 2;
      }

      return tok;
    }
  } // check for comparisons before isPunct so it doesn't catch == as =

  if (isPunct(text[i])) {
    column ++;

    Token result;
    
    result.type = classifyPunct(text[i]);
    result.text = malloc(2 * sizeof(char)); 
    result.text[0] = text[i];
    result.text[1] = '\0';
    result.text_len = 1;
    result.line = line;
    result.column = column; 

    *start = i + 1; // if you leave it as ++, it gets stuck on the parenthesis on the first test "print(1)", are you incrementing the pointer?

    printf("%c\n", text[i]);

    return result;
  }
  else if (isOperator(text[i])) {
    column ++;

    Token result;

    result.type = classifyOperator(text[i]);
    result.text = malloc(2 * sizeof(char));
    result.text[0] = text[i];
    result.text[1] = '\0';
    result.text_len = 1;
    result.line = line;
    result.column = column; 

    *start = i + 1; // WHY DID THIS THING NOT WORK AND GIVE ME TWO EQL_OP FOR ONE EQUAL WHEN IT WAS += 1???

    printf("%c\n", text[i]);

    return result;
  }

  /*
  {
    TokType type = classifyCompare(text[i], text[i + 1]);
    if (type != NONE) {
      Token tok;
      tok.type = type;
      tok.line = line;
      tok.column = column;

      if (type == LARGER_THAN || type == SMALLER_THAN){
        tok.text = malloc(2 * sizeof(char));
        tok.text[0] = text[i];
        tok.text[1] = '\0';
        tok.text_len = 1;
        *start = i + 1;
      }
      else {
        tok.text = malloc(3 * sizeof(char));
        tok.text[0] = text[i];
        tok.text[1] = text[i + 1];
        tok.text[2] = '\0';
        tok.text_len = 2;
        *start = i + 2;
      }

      return tok;
    }
  }
  */
  
  /*
  else if (isWhitespace(text[i])) {
    // line = line + (text[i] == '\n');
    // column = column * (text[i] != '\n');

    // column ++;
    if (i == size) {
      // return token with type EOF
      Token result;
      result.type = END_OF_FILE;

      return result;
    }
    
    *start += 1;
  }
  */

  // printf("Got here 1\n");

  bool isText = false;
  bool isNumber = false;

  if ('0' <= text[i] && text[i] <= '9') {
    isNumber = true;
  }
  else if (text[i] == '-' && (i + 1) < size) {
    if ('0' <= text[i + 1] && text[i + 1] <= '9') {
      isNumber = true;
    }
  }
  else {
    isText = true;
  }

  // printf("Got here 2\n");

  char* tok_text = newDynArr(char, 1);

  // printf("Made dynArr\n");

  while (sameType(isNumber, text[i]) && !isPunct(text[i]) && !isWhitespace(text[i]) && !isOperator(text[i]) && text[i] != EOF && i < size) {
    dynPush(tok_text, text[i]);
    i ++;
    column ++;

    // printf();

    /*
    if (dynGetSize(tok_text) >= 2) { // check for potential compare operator
      TokType type = classifyCompare(tok_text[0], tok_text[1]);
      if (type != NONE) {
        Token tok;
        tok.type = type;
        tok.line = line;
        tok.column = column;

        if (type == LARGER_THAN || type == SMALLER_THAN){
          tok.text = malloc(2 * sizeof(char));
          tok.text[0] = tok_text[0];
          tok.text[1] = '\0';
          tok.text_len = 1;
        }
        else {
          tok.text = malloc(3 * sizeof(char));
          tok.text[0] = tok_text[0];
          tok.text[1] = tok_text[1];
          tok.text[2] = '\0';
          tok.text_len = 2;
        }

        *start = i + 1;

        return tok;
      }  
    }

    */
    
    // printf("%c %d\n", text[i], i);
  }

  {
    char end = '\0';
    dynPush(tok_text, end);
  }

  // i --;
  *start = i;

  // make the damn token
  
  for (int i = 0; i < dynGetSize(tok_text); i ++) {
    printf("%c", tok_text[i]);
  }

  printf("\n");

  Token tok; // dummy uninitialised token
  size_t len = dynGetSize(tok_text);
  tok.text = malloc(sizeof(char) * len);
  memcpy(tok.text, tok_text, sizeof(char) * len);
  tok.text_len = len - 1;
  tok.line = line;
  tok.column = column;
  
  if (isNumber) {
    tok.type = NUMBER;
    // tok.num_val = strtold(tok.text, NULL);
    tok.num_val = atof(tok.text);
  }
  else {
    // if (isStringLiteral(*tok_text, dynGetSize(tok_text))) {
      // do this later
      // TODO
    // }
    tok.type = IDENTIFIER;
  }

  return tok;
}




