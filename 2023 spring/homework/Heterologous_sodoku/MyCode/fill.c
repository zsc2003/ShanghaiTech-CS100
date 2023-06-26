#include <stdio.h>
#include <stdlib.h>

int checkOneNumber(int (*board)[9], int row, int col) {
    int num = board[row][col];
    //Judge whether the row is valid
    for(int c = 0 ; c < 9 ; ++c)
        if(c != col && board[row][c] == num)
            return 0;
    //Judge whether the column is valid
    for(int r = 0 ; r < 9 ; ++r)
        if(r != row && board[r][col] == num)
            return 0;
    //Judge whether the palace is valid
    int rStart = row / 3 * 3;
    int cStart = col / 3 * 3;
    for(int rOffset = 0 ; rOffset < 3 ; ++rOffset)
        for(int cOffset = 0 ; cOffset < 3 ; ++cOffset) {
            int idr = rStart + rOffset;
            int idc = cStart + cOffset;
            if(idr != row && idc != col && num == board[idr][idc])
                return 0;
        }
    //Judge whether the "Horse Step is valid"
    for(int Offset1 = -2 ; Offset1 <= 2 ; Offset1 += 4)
        for(int Offset2 = -1 ; Offset2 <= 1 ; Offset2 += 2) {
            //case1: 3*2
            int idr1 = Offset1 + row;
            int idc1 = Offset2 + col;
            if(idr1 < 9 && idr1 >= 0 && idc1 < 9 && idc1 >= 0 && board[idr1][idc1] == num) return 0;
            //case2: 2*3
            int idr2 = Offset2 + row;
            int idc2 = Offset1 + col;
            if(idr2 < 9 && idr2 >= 0 && idc2 < 9 && idc2 >= 0 && board[idr2][idc2] == num) return 0;
        }
    return 1;
}

void fillShuDuRecursively(int (*board)[9], int level, bool* isSucceed) {
    if(level == 81) {
        *isSucceed = true;
        return;
    }
    int r = level / 9;
    int c = level % 9;
    if(board[r][c] != 0) {
        fillShuDuRecursively(board, level+1, isSucceed);
    }
    else {
        for(int num = 1 ; num < 10 ; ++num) {
            board[r][c] = num;
            if(checkOneNumber(board, r, c) == 1) {
                fillShuDuRecursively(board, level+1, isSucceed);
            }
            if(*isSucceed) return;
        }
        board[r][c] = 0;
    }
}

void fillShuDu(int (*board)[9]) {
    bool isSucceed = false;
    fillShuDuRecursively(board, 0, &isSucceed);
}

int main() {
    int board[9][9] = {{0,9,0,0,0,0,2,0,0},
                       {0,0,0,0,0,9,0,0,3},
                       {0,7,0,6,0,0,0,0,0},
                       {0,0,9,0,6,0,0,0,0},
                       {0,8,0,0,0,0,0,6,0},
                       {0,0,0,0,5,0,1,0,0},
                       {0,0,0,0,0,1,0,7,0},
                       {8,0,0,3,0,0,0,0,0},
                       {0,0,4,0,0,0,0,9,0}};
    fillShuDu(board);
    //print ans
    for(int i = 0 ; i < 9 ; ++i) {
        for(int j = 0 ; j < 9 ; ++j)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    //correctness check
    for(int i = 0 ; i < 9 ; ++i) {
        for(int j = 0 ; j < 9 ; ++j) {
            if(checkOneNumber(board, i, j) == 0) {
                printf("row : %d, col : %d", i, j);
                exit(1);
            }
        }
    }
    return 0;
}