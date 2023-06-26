#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define DEF_LIST_TYPE(type) typedef struct NODE_##type {type val; struct NODE_##type *next;} NODE_##type; typedef struct LIST_##type {NODE_##type *head, *tail;} LIST_##type; typedef void(*FUNC_##type)(type*);
#define DEF_LIST_INIT(type) void List_##type##_init(LIST_##type* list_ptr) {list_ptr->head=list_ptr->tail=NULL;}

#define DEF_LIST_ADD(type) void List_##type##_add(LIST_##type* list_ptr, type val) {\
if(list_ptr == NULL) exit(-1);\
if(list_ptr->head == NULL) {\
list_ptr->head = list_ptr->tail = (NODE_##type *)malloc(sizeof(NODE_##type));\
if(list_ptr->head == NULL) exit(-1);\
list_ptr->head->val = val; list_ptr->tail->next = NULL; return;}\
list_ptr->tail->next = (NODE_##type *)malloc(sizeof(NODE_##type));\
if(list_ptr->tail->next == NULL) exit(-1);\
list_ptr->tail = list_ptr->tail->next;\
list_ptr->tail->val = val; list_ptr->tail->next = NULL;}

#define DEF_LIST_FOREACH(type) void List_##type##_foreach(LIST_##type* list_ptr, FUNC_##type func) {\
if(list_ptr == NULL) exit(-1);\
NODE_##type* ptr=list_ptr->head;\
while(ptr != NULL){\
func(&ptr->val);ptr=ptr->next;}}

#define DEF_LIST_DEFS(type) DEF_LIST_TYPE(type);\
DEF_LIST_INIT(type);\
DEF_LIST_ADD(type);\
DEF_LIST_FOREACH(type)

#define NEW_LIST(type, list_val_name) LIST_##type list_val_name; List_##type##_init(&list_val_name)
#define LIST_ADD_ELEMENT(type, list, element) List_##type##_add(&list, element)
#define LIST_FOREACH(type, list, func) List_##type##_foreach(&list, func)
#endif /*_LINKED_LIST_H_*/