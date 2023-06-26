int checkOneNumber(const int (*board)[9], int row, int col) {
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