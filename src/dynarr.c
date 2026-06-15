#include "dynarr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t size;
  size_t capacity;

  size_t elem_size;
} DynHeader;

void* __dynarray_create(size_t type_size, size_t alloc_size) {
  DynHeader* arr = (DynHeader*)(malloc(sizeof(DynHeader) + (type_size * alloc_size)));

  if (arr == NULL){
    return NULL;
  }

  arr -> size = 0;
  arr -> capacity = (int)(alloc_size);
  arr -> elem_size = type_size;

  return arr + 1;
}

/*
void __dynarray_push(void* header, void* elem, size_t elem_size) {
  DynHeader* h = header;

  if (h -> size >= h -> capacity) {
    h -> capacity = h -> capacity == 0 ? 1 : (2 * h -> capacity);
    h = realloc(h, sizeof(DynHeader) + h -> capacity * h -> elem_size);
  }
  
  if (elem_size != h -> elem_size) {
    printf("ERROR: Unable to push to array, types not of the same size\n");
    return;
  }
  
  h --;
  h -> size ++;
  h ++;

  mempcpy(h + ((h -> size) - 1) * h -> elem_size, elem, elem_size);

  *header = h;
}
*/

size_t __dynarray_size(void* header) {
  return ((DynHeader*)(header) - 1) -> size;
}

size_t __dynarray_cap(void* header) {
  return ((DynHeader*)(header) - 1) -> capacity;
}

void __dynarray_push(void** header, void* elem, size_t elem_size) {
  void* data_ptr = *header;
  
  DynHeader* h = (DynHeader*)(data_ptr) - 1;

  if (elem_size != h -> elem_size){
    printf("ERROR: Unable to push to array, types not of the same size\n");
    return;
  }

  if (h -> size >= h -> capacity) {
    size_t new_cap = h -> capacity == 0 ? 1 : (2 * h -> capacity);
    void* new_mem = realloc(h, sizeof(DynHeader) + new_cap * (h -> elem_size));

    if (new_mem == NULL) {
      printf("ERROR: Unable to reallocate space for dynamic array\n");
      return;
    }

    h = (DynHeader*) new_mem;
    h -> capacity = new_cap;
    
    data_ptr = h + 1;
    *header = data_ptr;
  }

  void* dest = (char*)(data_ptr) + (h -> size * h -> elem_size); // casted to char pointer so we can offset by bytes, not by sizeof(DynHeader)
  memcpy(dest, elem, elem_size);
  h -> size ++;
}

void __dynarray_put(void** header, void* elem, size_t elem_size, int pos) {
  void* data_ptr = *header;

  DynHeader* h = (DynHeader*)(data_ptr) - 1;

  if (elem_size != h -> elem_size) {
    printf("ERROR: Unable to put element in array, types not of the same size");
    return;
  }

  if (pos >= h -> capacity){
    size_t new_cap = h -> capacity == 0 ? 1 : (2 * h -> capacity);
    while (new_cap <= pos) {
      new_cap *= 2;
    }
    
    void* new_mem = realloc(h, sizeof(DynHeader) + new_cap * (h -> elem_size));

    if (new_mem == NULL) {
      printf("ERROR: Unable to allocate enough space to extend to get to the %dth position of the array", pos);
      return;
    }

    h = (DynHeader*) new_mem;
    h -> capacity = new_cap;

    data_ptr = h + 1;
    *header = data_ptr;
  }

  if (pos >= (int)(h -> size)) {
    if (pos > (int)(h -> size)) {
      void* gap_start = (char*)(data_ptr) + (h -> size * h -> elem_size);
      size_t gap_bytes = (pos - h -> size) * (h -> elem_size);

      memset(gap_start, 0, gap_bytes);
    }

    h -> size = pos + 1;
  }

  void* dest = (char*)(data_ptr) + (pos * h -> elem_size);
  memcpy(dest, elem, elem_size);
}


