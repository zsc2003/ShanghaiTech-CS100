#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int face[501][501];
bool visited[501][501];

int encode_face(char ch) {
  if (ch == 'U')
    return 0;
  if (ch == 'R')
    return 1;
  if (ch == 'D')
    return 2;
  assert(ch == 'L');
  return 3;
}

int encode_direction(char ch) {
  if (ch == 'F')
    return 0;
  if (ch == 'R')
    return 1;
  if (ch == 'B')
    return 2;
  assert(ch == 'L');
  return 3;
}

bool valid_coord(int row, int col, int r, int c) {
  return row >= 1 && row <= r && col >= 1 && col <= c;
}

int main(void) {
  int r, c, q;
  scanf("%d %d %d", &r, &c, &q);
  for (int i = 1; i <= r; ++i) {
    for (int j = 1; j <= c; ++j) {
      char ch;
      scanf(" %c", &ch);
      face[i][j] = encode_face(ch);
    }
  }
  int row = 0, col = 0;
  scanf("%d %d", &row, &col);

  for (int i = 0; i != q; ++i) {
    char direction_str[6] = {0};
    int length;
    scanf("%s %d", direction_str, &length);
    char ch = direction_str[0];
    int direction = encode_direction(ch);

    // **MAGIC HAPPENS**
    int magic = (face[row][col] + direction) % 4;
    if (magic == 0)
      row -= length;
    else if (magic == 1)
      col += length;
    else if (magic == 2)
      row += length;
    else
      col -= length;

    if (valid_coord(row, col, r, c) && !visited[row][col]) {
      printf("(%d, %d)\n", row, col);
      visited[row][col] = true;
    } else {
      puts("Mistake!");
      break;
    }
  }

  return 0;
}