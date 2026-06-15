#include <stddef.h>

#ifndef DYNARR_H
#define DYNARR_H

void* __dynarray_create(size_t type_size, size_t alloc_size);

void __dynarray_push(void** header, void* elem, size_t elem_size);

void __dynarray_put(void** header, void* elem, size_t elem_size, int pos);

#define newDynArr(__type, __size) __dynarray_create((size_t)(sizeof(__type)), (size_t)(__size))

#define dynPush(__arr, __elem) __dynarray_push((void**) &(__arr), (void*) &(__elem), (size_t)(sizeof(__elem)))

#define dynPut(__arr, __elem, __pos) __dynarray_put((void**) &(__arr), (void*) &(__elem), (size_t)(sizeof(__elem)), (int)(__pos))

#endif


