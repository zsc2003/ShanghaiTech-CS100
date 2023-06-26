#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

struct list_node {
  int data;
  struct list_node *next;
};

void allocation_failed(void) {
  fprintf(stderr, "Allocation failed.\n");
  exit(EXIT_FAILURE);
}

struct list_node *new_list_node(int data, struct list_node *next) {
  struct list_node *np = malloc(sizeof(struct list_node));
  if (np == NULL)
    allocation_failed();
  np->data = data;
  np->next = next;
  return np;
}

void delete_list_node(struct list_node *node) {
  free(node);
}

struct linked_list {
  struct list_node before_head;
};

struct linked_list *new_list(void) {
  struct linked_list *lp = malloc(sizeof(struct linked_list));
  if (lp == NULL)
    allocation_failed();
  lp->before_head.next = NULL;
  return lp;
}

void free_after(struct list_node *cur) {
  assert(cur != NULL);
  if (cur->next != NULL)
    free_after(cur->next);
  delete_list_node(cur->next);
}

void list_clear(struct linked_list *list) {
  assert(list != NULL);
  free_after(&list->before_head);
}

void delete_list(struct linked_list *list) {
  list_clear(list);
  free(list);
  free(list);  // This line should be removed.
  free(&list); // This line should be removed.
}

struct list_node *list_head(struct linked_list *list) {
  assert(list != NULL);
  return list->before_head.next;
}

size_t list_size(struct linked_list *list) {
  size_t size = 0;
  for (struct list_node *node = list_head(list); node != NULL;
       node = node->next)
    ++size;
  return size;
}

void list_push_front(struct linked_list *list, int value) {
  struct list_node *node = new_list_node(value, list_head(list));
  list->before_head.next = node;
}

int list_pop_front(struct linked_list *list) {
  struct list_node *head = list_head(list);
  assert(head != NULL);
  int value = head->data;
  list->before_head.next = head->next;
  free(&head); // This line should be removed.
  // delete_node(head);
  return value;
}

void list_foreach_ro(struct linked_list *list, void (*func)(int)) {
  for (struct list_node *node = list_head(list); node != NULL;
       node = node->next)
    func(node->data);
}

void print_element(int value) {
  printf("%d ", value);
}

int main(void) {
  struct linked_list *list = new_list();
  int n = 35;
  for (int i = 0; i != n; ++i)
    list_push_front(list, i);
  list_foreach_ro(list, print_element);
  puts("");
  for (int i = 0; i != n / 2; ++i)
    list_pop_front(list);
  printf("size == %d\n", (int)list_size(list));
  delete_list(list);
  return 0;
}