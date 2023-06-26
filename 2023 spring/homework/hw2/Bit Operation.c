#include<stdio.h>

typedef unsigned long long ull;

ull lowbit(ull x)
{
	return x&(-x);
}

int bit(ull x)
{
	int num = 0;
	while(x!=0)
	{
		++num;
		x >>= 1;
	}
	return num;
}

int main()
{
	ull x;
	int m;
	scanf("%llu%d",&x,&m);
	ull q = (x >> (m + 1));
	ull p = (q << (m + 1)) ^ x;
	// printf("p = %llu\nq = %llu\n",p,q);
	// printf("bits = %d\n", bit(q));
	
	ull r = (p << bit(q)) | q;
	// printf("%llu\n",r);

	int b = bit(lowbit(r)) - 1;

	printf("%llu %d",r, b);
	return 0;
}/*
18446744073709551615 12
18446744073709551615 0
*/
