#include "./ans1.c"
#include "stdio.h"

int main() {
    int board[9][9];
    for(int r = 0 ; r < 9 ; ++r)
        for(int c = 0 ; c < 9 ; ++c)
            scanf("%d", &board[r][c]);
    for(int r = 0 ; r < 9 ; ++r)
        for(int c = 0 ; c < 9 ; ++c) 
            if(checkOneNumber(board, r, c) == 0) {
                printf("0");
                goto End;
            }
    printf("1");
    End:
    return 0;
}

