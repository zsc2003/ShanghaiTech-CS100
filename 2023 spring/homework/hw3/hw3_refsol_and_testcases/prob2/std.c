#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char next_lower_letter(char letter) {
  assert(islower(letter));
  // return 'a' + (letter - 'a' + 1) % 26;
  return letter == 'z' ? 'a' : letter + 1;
}

void build_encoding_alphabet(const char *keyword, char *out_alphabet) {
  memset(out_alphabet, 0, 27 * sizeof(char));

  // Add every letter in keyword to the alphabet.
  int len = strlen(keyword);
  for (int i = 0; i < len; i++) {
    if (strchr(out_alphabet, tolower(keyword[i])) == NULL) {
      out_alphabet[strlen(out_alphabet)] = tolower(keyword[i]);
    }
  }

  // Fill the rest of the alphabet with a moving pointer.
  // A more common "for (int i = 0; i < 26; i++)" will also work,
  // but please take this as a demonstration of pointer usage.
  for (char *curr_pos = out_alphabet + strlen(out_alphabet);
       curr_pos - out_alphabet < 26; curr_pos++) {
    char next_letter = next_lower_letter(*(curr_pos - 1));
    while (strchr(out_alphabet, next_letter) != NULL) {
      next_letter = next_lower_letter(next_letter);
    }
    *curr_pos = next_letter;
  }

  assert(strlen(out_alphabet) == 26);
  // NOTE: This alphabet is for encoding. For decoding it needs to be reversed.
}

void build_decoding_alphabet(const char *keyword, char *out_alphabet) {
  memset(out_alphabet, 0, 27 * sizeof(char));
  char encoding_alphabet[27];
  build_encoding_alphabet(keyword, encoding_alphabet);

  // Reverses encoding alphabet for decoding.
  int len = strlen(encoding_alphabet);
  assert(len == 26);
  for (int i = 0; i < len; i++) {
    out_alphabet[encoding_alphabet[i] - 'a'] = 'a' + i;
  }

  assert(strlen(out_alphabet) == 26);
}

int main(void) {
  char keyword[101];
  scanf("%s", keyword);

  char alphabet[27];
  // build_encoding_alphabet(keyword, alphabet);
  // build_decoding_alphabet(keyword, alphabet);

  getchar();

  int curr_char;
  while ((curr_char = getchar()) != EOF && curr_char != '\n') {
    if (isupper(curr_char)) {
      putchar(toupper(alphabet[curr_char - 'A']));
    } else if (islower(curr_char)) {
      putchar(alphabet[curr_char - 'a']);
    } else {
      putchar(curr_char);
    }
  }
  putchar('\n');
  return 0;
}
