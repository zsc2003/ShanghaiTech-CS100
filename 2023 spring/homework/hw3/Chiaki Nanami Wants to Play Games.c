#include<stdio.h>

int a[2000010];

int main()
{
	int n, t, ans = 0;
	long long p;
	char c;
	int maxn = 0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	while(c != ',')
	    	c = getchar();
	    scanf("%lld,%d", &p, &t);
	    while(c != '\n')
	    	c = getchar();
	    	
	    a[t] += p;
	    if(t > maxn)
	    	maxn = t;
    }
    
    for(int i = 1; i <= maxn; ++i)
    	if(a[i] > a[ans])
    		ans = i;
    printf("%d", ans);
    return 0;
}
/*
3
(Goose Goose Duck,2,1)
(CSGO,4,2)
(Among us,3,1)
*/
