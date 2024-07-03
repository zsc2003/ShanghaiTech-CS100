#include <stddef.h>

int hw3_islower(int ch) {
  return ch >= 'a' && ch <= 'z';
}

int hw3_isupper(int ch) {
  return ch >= 'A' && ch <= 'Z';
}

int hw3_isalpha(int ch) {
  return hw3_islower(ch) || hw3_isupper(ch);
}

int hw3_isdigit(int ch) {
  return ch >= '0' && ch <= '9';
}

int hw3_tolower(int ch) {
  return hw3_isupper(ch) ? ch - 'A' + 'a' : ch;
}

int hw3_toupper(int ch) {
  return hw3_islower(ch) ? ch - 'a' + 'A' : ch;
}

char *hw3_strchr(const char *str, int ch) {
  while (*str != '\0' && *str != (char)ch)
    ++str;
  if (*str == (char)ch)
    return (char *)str;
  else
    return NULL;
}

size_t hw3_strlen(const char *str) {
  size_t ans = 0;
  while (*str++ != '\0')
    ++ans;
  return ans;
}

char *hw3_strcpy(char *dest, const char *src) {
  char *save = dest;
  do
    *dest++ = *src;
  while (*src++ != '\0');
  return save;
}

char *hw3_strcat(char *dest, const char *src) {
  char *save = dest;
  while (*dest != '\0')
    ++dest;
  hw3_strcpy(dest, src);
  return save;
}

int hw3_strcmp(const char *lhs, const char *rhs) {
  while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
    ++lhs;
    ++rhs;
  }
  return *lhs - *rhs;
}