#include<stdio.h>

int main()
{
	int n, t, ans = 0;
	long long p, num = 0;
	char c;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	while(c != ',')
	    	c = getchar();
	    scanf("%lld,%d", &p, &t);
	    while(c != '\n')
	    	c = getchar();
        if(t == ans)
            num += p;
        else
		{
			num -= p;
			if(num <= 0)
			{
				ans = t;
				num = -num;
			}
        }
    }
    printf("%d", ans);
    return 0;
}
/*
3
(Goose Goose Duck,2,1)
(CSGO,4,2)
(Among us,3,1)
*/
