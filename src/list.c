#include "../include/list.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

ivy_list ivy_list_init(size_t t_obj_size) {
  return (ivy_list) { 
    .ptr = NULL,
    .size = 0,
    .obj_size = t_obj_size, 
  };
}

void ivy_list_push(ivy_list *list, void *el) {
  list->ptr = (void *) realloc(list->ptr, list->obj_size * (list->size + 1));
  assert(list->ptr != NULL && "Failed pushing to the list");
  memcpy(list->ptr + list->obj_size * list->size, el, list->obj_size);
  ++list->size;
}

void *ivy_list_get(ivy_list *list, size_t index) {
  assert(index < list->size && "Index out of bounds");
  return list->ptr + index * list->obj_size; 
}

void ivy_list_free(ivy_list *list) {
  if (list->ptr != NULL) {
    free(list->ptr);
  }
}
