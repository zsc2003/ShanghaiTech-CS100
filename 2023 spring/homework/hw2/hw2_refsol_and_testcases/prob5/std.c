#include <stdio.h>
#include <stdbool.h>

bool validCoord(int r, int c) {
  return r >= 0 && c >= 0 && r < 9 && c < 9;
}

bool checkOneNumber(int (*board)[9], int row, int col) {
  int num = board[row][col];
  // Judge whether the row is valid
  for (int c = 0; c < 9; ++c)
    if (c != col && board[row][c] == num)
      return false;
  // Judge whether the column is valid
  for (int r = 0; r < 9; ++r)
    if (r != row && board[r][col] == num)
      return false;
  // Judge whether the palace is valid
  int rStart = row / 3 * 3;
  int cStart = col / 3 * 3;
  for (int rOffset = 0; rOffset < 3; ++rOffset)
    for (int cOffset = 0; cOffset < 3; ++cOffset) {
      int idr = rStart + rOffset;
      int idc = cStart + cOffset;
      if (idr != row && idc != col && num == board[idr][idc])
        return false;
    }
  // Judge whether the "Horse Step is valid"
  static const int dr[] = {-1, -2, -2, -1, 1, 2, 2, 1};
  static const int dc[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  for (int i = 0; i != 8; ++i) {
    int r = row + dr[i], c = col + dc[i];
    if (validCoord(r, c) && board[row][col] == board[r][c])
      return false;
  }
  return true;
}

int main() {
  int board[9][9];
  for (int r = 0; r < 9; ++r)
    for (int c = 0; c < 9; ++c)
      scanf("%d", &board[r][c]);
  for (int r = 0; r < 9; ++r)
    for (int c = 0; c < 9; ++c)
      if (checkOneNumber(board, r, c) == false) {
        puts("0");
        return 0;
      }
  puts("1");
  return 0;
}
