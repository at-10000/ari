#include "tokens.h"

Token makeTok (TokType type, char* ) {}
/*
Token* replace_dot_for_structs (Token* toks) {
  Token* result = newDynArr(Token, 1);
  for (int i = 0; toks[i].type != END_OF_FILE; i ++) {
    if (toks[i].type == DOT_OP && (i + 2) < toks.size) {
      if (toks[i + 2].type != R_PAREN) {
        dynPush(result, toks[i + 1]);
      }
    }
    else {
      dynPush(result, toks[i]);
    }
  }
}
*/

/*
bool isInsideMethodChain (token tok) {
  if (tok.type == NUMBER || tok.type == STR_LIT || tok.type == tok.text[0] == '\"')
}
*/

Token* preprocessor (Token* toks) {
  return toks;
}

// Make a function to get the method chain


