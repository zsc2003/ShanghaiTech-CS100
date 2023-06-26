#include<stdio.h>

typedef long long ll;
int main()
{
	ll a[110];
	int n,m = 0;
	ll f;
	
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lld",&f);
		if(f > 0)
			a[++m] = f * f;
	}
	for(int i=m;i>=1;--i)
		printf("%lld\n", a[i]);
	printf("%d\n",m);
	return 0;
}
