#include <stddef.h>

int hw4_islower(int ch) {
  return ch >= 'a' && ch <= 'z';
}

int hw4_isupper(int ch) {
  return ch >= 'A' && ch <= 'Z';
}

int hw4_isalpha(int ch) {
  return hw4_islower(ch) || hw4_isupper(ch);
}

int hw4_isdigit(int ch) {
  return ch >= '0' && ch <= '9';
}

int hw4_tolower(int ch) {
  return hw4_isupper(ch) ? ch - 'A' + 'a' : ch;
}

int hw4_toupper(int ch) {
  return hw4_islower(ch) ? ch - 'a' + 'A' : ch;
}

char *hw4_strchr(const char *str, int ch) {
  char *pos = (char *)str;
  while (*pos != '\0' && *pos != (char)ch)
    ++pos;
  if (*pos == (char)ch)
    return pos;
  else
    return NULL;
}

size_t hw4_strlen(const char *str) {
  size_t ans = 0;
  while (*str++ != '\0')
    ++ans;
  return ans;
}

char *hw4_strcpy(char *dest, const char *src) {
  char *save = dest;
  while (*src != '\0')
    *dest++ = *src++;
  *dest = '\0';
  return save;
}

char *hw4_strcat(char *dest, const char *src) {
  char *save = dest;
  while (*dest != '\0')
    ++dest;
  hw4_strcpy(dest, src);
  return save;
}

int hw4_strcmp(const char *lhs, const char *rhs) {
  while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
    ++lhs;
    ++rhs;
  }
  return *lhs - *rhs;
}