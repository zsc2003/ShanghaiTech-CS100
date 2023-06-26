#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char keyword[102];

char encoding[27];

int read_keyword(void) {
  fgets(keyword, 102, stdin);

  // What does `fgets` actually do?
  // How many characters at most will `fgets` read from the input?
  // Does `fgets` read the newline character ('\n') at the end?
  // -- If so, is that newline character put into the string?
  // Does `fgets` put a '\0' to the end of the string?

  // For the answers of these questions, see en.cppreference.com/w/c/io/fgets

  // If you use `fgets` without being able to answer these questions correctly,
  // YOU ARE HEADING FOR TROUBLE.

  int len_keyword = strlen(keyword);
  assert(keyword[len_keyword - 1] == '\n');
  keyword[len_keyword - 1] = '\0';
  --len_keyword;
  assert(len_keyword >= 0);
  return len_keyword;
}

void generate_encoding(int len_keyword) {
  bool used[26] = {0};
  int len_encoding = 0;
  for (int i = 0; i != len_keyword; ++i) {
    char ch = tolower(keyword[i]);
    if (!used[ch - 'a']) {
      used[ch - 'a'] = true;
      assert(len_encoding < 26);
      encoding[len_encoding++] = ch;
    }
  }
  assert(len_encoding <= 26);
  char cur = encoding[len_encoding - 1];
  for (int i = len_encoding; i != 26; ++i) {
    while (used[cur - 'a']) {
      ++cur;
      if (cur == 'z' + 1)
        cur = 'a';
    }
    encoding[i] = cur;
    used[cur - 'a'] = true;
  }
  for (int i = 0; i != 26; ++i)
    assert(used[i]);
}

char decode(char ch) {
  if (isalpha(ch)) {
    bool is_upper = isupper(ch);
    ch = tolower(ch);
    int pos = -1;
    for (int i = 0; i != 26; ++i)
      if (encoding[i] == ch) {
        pos = i;
        break;
      }
    assert(pos != -1);
    return pos + (is_upper ? 'A' : 'a');
  } else
    return ch;
}

int main(void) {
  int len_keyword = read_keyword();

  generate_encoding(len_keyword);

  // There's no need to store the ciphertext!
  char ch = getchar();
  while (ch != EOF && ch != '\n') {
    putchar(decode(ch));
    ch = getchar();
  }
  puts("");
  return 0;
}