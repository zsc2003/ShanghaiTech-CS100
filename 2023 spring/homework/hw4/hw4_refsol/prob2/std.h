#ifndef CS100_MEMCHECK_STD_H
#define CS100_MEMCHECK_STD_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record {
  void *ptr;
  size_t size;
  int line_no;
  const char *file_name;
};

struct Record records[MAX_RECORDS];
size_t record_cnt = 0;

void try_add_record(void *ptr, size_t size, int line, const char *file) {
  if (record_cnt == MAX_RECORDS - 1) {
    fputs("Too many allocations!", stderr);
    exit(EXIT_FAILURE);
  }
  records[record_cnt++] = (struct Record){
      .ptr = ptr, .size = size, .line_no = line, .file_name = file};
}

size_t find_record(void *ptr) {
  for (size_t i = 0; i != record_cnt; ++i)
    if (records[i].ptr == ptr)
      return i;
  return -1;
}

void *recorded_malloc(size_t size, int line, const char *file) {
  void *ptr = malloc(size);
  if (ptr != NULL)
    try_add_record(ptr, size, line, file);
  return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line,
                      const char *file) {
  void *ptr = calloc(cnt, each_size);
  if (ptr != NULL)
    try_add_record(ptr, cnt * each_size, line, file);
  return ptr;
}

void recorded_free(void *ptr, int line, const char *file) {
  if (ptr == NULL)
    return;
  size_t idx = find_record(ptr);
  if (idx == (size_t)-1) {
    printf("Invalid free in file %s, line %d\n", file, line);
    return;
  }
  records[idx].ptr = NULL;
  free(ptr);
}

void check_leak(void) __attribute__((destructor));

void check_leak(void) {
  puts("Summary:");
  int unfreed_records = 0;
  size_t unfreed_size = 0;
  for (size_t i = 0; i != record_cnt; ++i)
    if (records[i].ptr != NULL) {
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

#define calloc(CNT, EACH_SIZE)                                                 \
  recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)

#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

#endif // CS100_MEMCHECK_STD_H
