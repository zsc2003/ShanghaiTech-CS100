#include "stdio.h"
#include "stdlib.h"

int** MagicSquare(int n)
{
	int square=n*n;
    int **ans=(int**)malloc(sizeof(int*)*n);
    int i,j;
	for(i=0;i<n;++i)
	{
		ans[i]=malloc(sizeof(int)*n);
		for(j=0;j<n;++j)
			*(*(ans+i)+j)=0;
	}
		
    int mid=n>>1;
    int x=0,y=mid;
    int step=1;
    while(step!=(square+1))
    {
		if(x<0)x+=n;
		if(y<0)y+=n;
		if(x>=n)x-=n;
    	if(y>=n)y-=n;
    	if((*(*(ans+x)+y))!=0)
    	{
    		if(step==square)break;
    		x+=2;
    		y--;
    		continue;
		}
		*(*(ans+x)+y)=step;
    	step++;
    	--x;
    	++y;
	}
    return ans;
}

void FreeMagicSquare(int** magicSquare, int n){
    int i;
	for(i=0;i<n;++i)
		free((void *)magicSquare[i]);
	free((void *)magicSquare);
	return;
}

int main(){
    int n;
    scanf("%d", &n); // Please input a positive odd number.
    int** magicSquare = MagicSquare(n);
    int i,j;
	for( i = 0; i < n; i++){
        for( j = 0; j < n; j++){
            printf("%4d", magicSquare[i][j]);
        }
        printf("\n");
    }
    FreeMagicSquare(magicSquare, n);
    return 0;
}
