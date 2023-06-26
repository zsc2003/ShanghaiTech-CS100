#include <stdbool.h>
#include <stdio.h>

bool rowValid(int (*board)[9], int row, int col) {
  for (int c = 0; c < 9; ++c)
    if (c != col && board[row][c] == board[row][col])
      return false;
  return true;
}

bool colValid(int (*board)[9], int row, int col) {
  for (int r = 0; r < 9; ++r)
    if (r != row && board[r][col] == board[row][col])
      return false;
  return true;
}

bool palaceValid(int (*board)[9], int row, int col) {
  int rStart = row / 3 * 3;
  int cStart = col / 3 * 3;
  for (int rOffset = 0; rOffset < 3; ++rOffset)
    for (int cOffset = 0; cOffset < 3; ++cOffset) {
      int idr = rStart + rOffset;
      int idc = cStart + cOffset;
      if ((idr != row || idc != col) && board[idr][idc] == board[row][col])
        return false;
    }
  return true;
}

bool horseValid(int (*board)[9], int row, int col) {
  static const int dr[] = {-1, -2, -2, -1, 1, 2, 2, 1};
  static const int dc[] = {-2, -1, 1, 2, 2, 1, -1, -2};
  for (int i = 0; i != 8; ++i) {
    int r = row + dr[i], c = col + dc[i];
    if (validCoord(r, c) && board[row][col] == board[r][c])
      return false;
  }
  return true;
}

bool checkOneNumber(int (*board)[9], int row, int col) {
  return rowValid(board, row, col) && colValid(board, row, col) &&
         palaceValid(board, row, col) && horseValid(board, row, col);
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
