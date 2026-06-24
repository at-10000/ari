#include <stddef.h>

#ifndef DYNARR_H
#define DYNARR_H

size_t _dynarray_size(void* header);

size_t _dynarray_cap(void* header);

void* _dynarray_create(size_t type_size, size_t alloc_size);

void _dynarray_push(void** header, void* elem, size_t elem_size);

void _dynarray_set(void** header, void* elem, size_t elem_size, int pos);

void* _dynarray_elem_at(void* header, int pos);

#define newDynArr(type, size) _dynarray_create((size_t)(sizeof(type)), (size_t)(size))

#define dynPush(arr, elem) _dynarray_push((void**) &(arr), (void*) &(elem), (size_t)(sizeof(elem)))

#define dynSet(arr, elem, pos) _dynarray_set((void**) &(arr), (void*) &(elem), (size_t)(sizeof(elem)), (int)(pos))

#define dynGetValue(arr, type, pos) (*(type*)_dynarray_elem_at((void*)(arr), (int)(pos)))

#define dynGetPointer(arr, type, pos) (type*)_dynarray_elem_at((void*)(arr), (int)(pos))

#define dynGetSize(arr) _dynarray_size((void*)(arr))

#define dynGetCap(arr) _dynarray_cap((void*)(arr))

// TODO: Make a function to delete an element at a certain position and offset everything. Make another one to pop last element (just decrease the size)

// TODO: Turn dynPush and dynPut into functions so you can push and put literals as well, not variables. Check if that could work

// TODO: Maybe make it so you can pass the variable names as well as a parameter to the functions, convert the text for arr to a string somehow. 
// This would be helpful for debugging, as the functions would tell you what was the array you tried to push into but didn't work

// TODO: Make a function to free a dynArr, otherwise you will just get a memory leak. Dumbass.

#endif



