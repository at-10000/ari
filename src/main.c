#include <stdio.h>
#include "dynarr.h"

int main(int argc, char *argv[]) {
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  
  if (fptr == NULL){
    printf("ERROR: File could not be opened. \n");
  }

  int* arr = newDynArr(int, 2);
  arr[1] = 4;
  int newelem = 16;
  dynPush(arr, newelem);
  printf("%d %d\n", arr[0], arr[1]);
  
  newelem = 8;
  dynPut(arr, newelem, 0);

  printf("%d %d\n", arr[0], arr[1]);
}


