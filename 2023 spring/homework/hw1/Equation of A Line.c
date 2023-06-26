#include <stdio.h>

int main()
{
	int x1,x2,y1,y2;
    scanf("(%d,%d)\n",&x1,&y1);
    scanf("(%d,%d)",&x2,&y2);
    //printf("%d %d %d %d\n",x1,y1,x2,y2);
    if(x1 == x2)
    {
        printf("x = %.2f\n",(double)x1);
        return 0;
    }
    double k = (double)(y1-y2)/(double)(x1-x2);
    if(-0.001f < k && k < 0.001f)
        k = 0.00f;
    double b = (double)y1 - (double)x1 * k;
    if(b < 0.001f)
        printf("y = %.2lfx - %.2lf\n",k,-b);
    else
        printf("y = %.2lfx + %.2lf\n",k,b);
	return 0;
}
