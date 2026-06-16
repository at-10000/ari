#include <tokens.h>
#include <stdbool.h>

bool isPunct (char c) {
  int i = 0;
  while (punctuation[i] != EOF) {
    if (punctuation[i] == c) {
      return 0;
    }
    i ++;
  }
  return i;
}

Token nextTok (char* text, size_t start, size_t size) {
  int i = start;
  
}


