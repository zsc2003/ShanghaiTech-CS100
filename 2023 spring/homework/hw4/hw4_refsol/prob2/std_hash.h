#ifndef CS100_MEMCHECK_HASH_H
#define CS100_MEMCHECK_HASH_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_RECORDS 1009

struct Record {
  void *ptr;              // address of the allocated memory
  size_t size;            // size of the allocated memory
  int line_no;            // line number, at which a call to malloc or calloc happens
  const char *file_name;  // name of the file, in which the call to malloc or calloc happens
  bool removed;
};

struct Record records[MAX_RECORDS];
int total_records = 0;

static inline int hash(void *ptr) {
  return ((intptr_t)ptr >> 4) % MAX_RECORDS;
}

static inline int probe(int h, int i) {
  return (h + i * i) % MAX_RECORDS;
}

static inline bool available(int loc) {
  return records[loc].removed || records[loc].ptr == NULL;
}

static inline bool untouched(int loc) {
  return !records[loc].removed && records[loc].ptr == NULL;
}

static inline bool occupied(int loc) {
  return records[loc].ptr != NULL;
}

void add_record(void *ptr, size_t size, int line, const char *file) {
  if (total_records == MAX_RECORDS) {
    fputs("Too many allocations!", stderr);
    exit(EXIT_FAILURE);
  }
  for (int h = hash(ptr), i = 0; i != MAX_RECORDS; ++i) {
    int loc = probe(h, i);
    if (available(loc)) {
      records[loc] = (struct Record){ptr, size, line, file, false};
      ++total_records;
      return;
    }
  }
}

int find_record(void *ptr) {
  for (int h = hash(ptr), i = 0; i != MAX_RECORDS; ++i) {
    int loc = probe(h, i);
    if (records[loc].ptr == ptr)
      return loc;
    if (untouched(loc))
      break;
  }
  return -1;
}

void remove_record(int loc) {
  records[loc].ptr = NULL;
  records[loc].removed = true;
  --total_records;
}

void *recorded_malloc(size_t size, int line, const char *file) {
  void *ptr = malloc(size);
  if (ptr != NULL)
    add_record(ptr, size, line, file);
  return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line, const char *file) {
  void *ptr = calloc(cnt, each_size);
  if (ptr != NULL)
    add_record(ptr, cnt * each_size, line, file);
  return ptr;
}

void recorded_free(void *ptr, int line, const char *file) {
  if (ptr == NULL)
    return;
  int loc = find_record(ptr);
  if (loc == -1) {
    printf("Invalid free in file %s, line %d\n", file, line);
    return;
  }
  remove_record(loc);
  free(ptr);
}

void check_leak(void) __attribute__((destructor));

void check_leak(void) {
  puts("Summary:");
  int unfreed_records = 0;
  size_t unfreed_size = 0;
  for (int i = 0; i != MAX_RECORDS; ++i)
    if (occupied(i)) {
      ++unfreed_records;
      unfreed_size += records[i].size;
      printf("%zu bytes memory not freed (allocated in file %s, line %d)\n",
             records[i].size, records[i].file_name, records[i].line_no);
    }
  if (unfreed_records != 0) {
    printf("%d allocation records not freed (%zu bytes in total).\n",
           unfreed_records, unfreed_size);
  } else
    puts("All allocations have been freed.");
}

#define malloc(SIZE) recorded_malloc(SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE) recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

#endif // CS100_MEMCHECK_HASH_H
