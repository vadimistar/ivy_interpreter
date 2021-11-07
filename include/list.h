#ifndef IVY_LIST_H
#define IVY_LIST_H

#include <stdlib.h>

typedef struct {
  void *ptr;
  size_t size;
  size_t obj_size;
} ivy_list;

ivy_list ivy_list_init(size_t obj_size);   
void ivy_list_push(ivy_list *list, void *el);
void *ivy_list_get(ivy_list *list, size_t index);
void ivy_list_free(ivy_list *list);

#endif//IVY_LIST_H
