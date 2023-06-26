#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

struct vector {
  int *data;
  size_t size, capacity;
};

struct vector *new_vector(void) {
  struct vector *vp = malloc(sizeof(struct vector));
  vp->data = NULL;
  vp->size = 0;
  vp->capacity = 0;
  return vp;
}

void allocation_failed(void) {
  fprintf(stderr, "Allocation failed.\n");
  exit(EXIT_FAILURE);
}

int *alloc_and_copy(size_t alloc_length, const int *source, size_t length) {
  int *new_data = malloc(alloc_length * sizeof(int));
  if (new_data == NULL)
    allocation_failed();
  for (size_t i = 0; i != length; ++i)
    new_data[i] = source[i];
  return new_data;
}

void vector_shrink_to_fit(struct vector *vector) {
  if (vector->size == vector->capacity)
    return;
  assert(vector->size < vector->capacity);
  int *new_data = alloc_and_copy(vector->size, vector->data, vector->size);
  // free(vector->data);
  vector->data = new_data;
  vector->capacity = vector->size;
}

void vector_grow(struct vector *vector, size_t new_capacity) {
  assert(new_capacity > vector->capacity);
  int *new_data = alloc_and_copy(new_capacity, vector->data, vector->size);
  free(vector->data);
  vector->data = new_data;
  vector->capacity = new_capacity;
}

void vector_push_back(struct vector *vector, int value) {
  assert(vector != NULL);
  if (vector->size == vector->capacity)
    vector_grow(vector, vector->capacity == 0 ? 1 : 2 * vector->capacity);
  vector->data[vector->size++] = value;
}

int vector_pop_back(struct vector *vector) {
  assert(vector != NULL);
  assert(vector->size >= 1u);
  return vector->data[--vector->size];
}

void delete_vector(struct vector *vector) {
  assert(vector != NULL);
  free(vector->data);
  free(&vector); // It should be free(vector);
}

int main(void) {
  int n = 35;
  struct vector *vector = new_vector();
  for (int i = 0; i != n; ++i)
    vector_push_back(vector, i);
  for (int i = 0; i != n / 2; ++i)
    vector_pop_back(vector);
  for (int i = 0; i != n * 2; ++i)
    vector_push_back(vector, i);
  vector_shrink_to_fit(vector);
  delete_vector(vector);
  return 0;
}
