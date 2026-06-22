#include <stdio.h>
#include <stdlib.h>

#include "dynarr.h"
#include "tokens.h"

int main(int argc, char *argv[]) {
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  
  if (fptr == NULL) {
    printf("ERROR: File could not be opened. \n");
    return 1;
  }
  
  unsigned int file_len = 0;

  {
    char c;
    while ((c = fgetc(fptr)) != EOF) {
      file_len ++;
    }
    printf("Total length of file: %d\n", file_len);
    rewind(fptr);
  }

  char* file_data = malloc((size_t)(file_len + 1));

  {
    unsigned int i = 0;
    char c;
    while ((c = fgetc(fptr)) != EOF) {
      file_data[i ++] = c;
    }
    file_data[i] = '\0';
  }

  printf("File text:\n");

  for (int i = 0; i < file_len; i ++) {
    printf("%c", file_data[i]);
  }

  printf("\n");

  Token* tokArr = newDynArr(Token, 1);

  unsigned int reading_pos = 0;
  Token currentTok;

  do {
    currentTok = nextTok(file_data, &reading_pos, file_len);
    dynPush(tokArr, currentTok);
  } while (currentTok.type != END_OF_FILE);

  printf("\n");

  for (int i = 0; i < dynGetSize(tokArr); i ++) {
    printTok(tokArr[i]);
    printf("\n");
  }

  return 0;
}




