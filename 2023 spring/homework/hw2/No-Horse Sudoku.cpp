#include<stdio.h>

int r[9], c[9], p[9];
int mvx[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
int mvy[8] = {-2, -2, -1, 1, 2, 2, 1, -1};

int calc(int row, int col)
{
	int r1 = row / 3;
	int c1 = col / 3;
	return 3 * r1 + c1;
}

int checkOneNumber(int (*board)[9], int row, int col)
{
	if((r[row] & (1 << board[row][col])) != 0)
		return 0;
	r[row] |= (1 << board[row][col]);
	
	if((c[col] & (1 << board[row][col])) != 0)
		return 0;
	c[col] |= (1 << board[row][col]);
	
	int palace = calc(row, col);
	if((p[palace] & (1 << board[row][col])) != 0)
		return 0;
	p[palace] |= (1 << board[row][col]);
	
	for(int i = 0; i < 8; ++i)
	{
		int dx = row + mvx[i];
		int dy = col + mvy[i];
		if(dx < 0 || dx > 8)
			continue;
		if(dy < 0 || dy > 8)
			continue;
		if(board[row][col] == board[dx][dy])
			return 0;
	}
	return 1;	
}

int check(int (*board)[9], int row, int col)
{
	for(int i = 0; i < row; ++i)
		for(int j = 0; j < col; ++j)
			if(checkOneNumber(board, i, j) == 0)
			{
				// printf("%d %d\n", i, j);
				return 0;
			}
	
	return 1;
}

int main()
{
	int board[9][9];
	int n = 9, m = 9;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d",&board[i][j]);
	printf("%d\n",check(board, 9, 9));
	return 0;
}
