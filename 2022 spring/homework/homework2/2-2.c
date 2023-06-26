#include <stdio.h>
#include<stdarg.h>

int calc(int x)
{
	if(x==0)return 1;
	int ans=0;
	if(x<0)
	{
		x=-x;
		ans++;
	}
	while(x!=0)
	{
		ans++;
		x/=10;
	}
	return ans;
}

int max(int n,...)
{
	int ans=0,x,i;
	va_list list;
	va_start(list,n);
	for(i=1;i<=n;++i)
	{
		x=va_arg(list,int);
		if(ans<x)
			ans=x;
	}
	va_end(list);
	return ans;
}

void add(int a, int b)
{
    int c=a+b;
    int la=calc(a);
    int lb=calc(b);
    int lc=calc(c);
	int len=max(3,la,lb,lc)+2;
	int i;
	for(i=1;i<=len-la;++i)printf("%c",' ');
	printf("%d\n+",a);
	for(i=1;i<=len-lb-1;++i)printf("%c",' ');
	printf("%d\n",b);
	for(i=1;i<=len;++i)printf("%c",'-');
	printf("\n");
	for(i=1;i<=len-lc;++i)printf("%c",' ');
	printf("%d\n",c);
}

void subtract(int a, int b)
{
	int c=a-b;
    int la=calc(a);
    int lb=calc(b);
    int lc=calc(c);
	int len=max(3,la,lb,lc)+2;
	int i;
	for(i=1;i<=len-la;++i)printf("%c",' ');
	printf("%d\n-",a);
	for(i=1;i<=len-lb-1;++i)printf("%c",' ');
	printf("%d\n",b);
	for(i=1;i<=len;++i)printf("%c",'-');
	printf("\n");
	for(i=1;i<=len-lc;++i)printf("%c",' ');
	printf("%d\n",c);
}

void multiply(int a, int b)
{
    int x,i,l,l_length;
    int cnt=0;
    int c=a*b;
    int la=calc(a);
    int lb=calc(b);
    int lc=calc(c);
    int len=max(3,la,lb,lc);
    x=b;
    while(x!=0)
    {
    	l=a*(x%10);
    	//printf("%d\n",l);
		l_length=calc(l);
    	len=max(2,len,l_length+cnt);
    	x/=10;
    	++cnt;
	}
	len+=2;
	//-------------------------------------------
	for(i=1;i<=len-la;++i)printf("%c",' ');
	printf("%d\nx",a);
	for(i=1;i<=len-lb-1;++i)printf("%c",' ');
	printf("%d\n",b);
	for(i=1;i<=len;++i)printf("%c",'-');
	printf("\n");
	if(c==0)
	{
		for(i=1;i<=len-lc;++i)printf("%c",' ');
		printf("%d\n",c);
		return;
	}
	x=b;
	cnt=0;
	while(x!=0)
    {
		l=a*(x%10);
		if(l==0)
		{
			++cnt;
			x/=10;
			continue;
		}
		l_length=calc(l);
    	for(i=1;i<=len-l_length-cnt;++i)printf("%c",' ');
    	printf("%d\n",l);
    	x/=10;
    	++cnt;
	}
	
	for(i=1;i<=len;++i)printf("%c",'-');
	printf("\n");
	for(i=1;i<=len-lc;++i)printf("%c",' ');
	printf("%d\n",c);
}

int main()
{
    int a, b;
    char op;
    scanf("%d %c %d", &a, &op, &b);
    switch (op) {
        case '+':
            add(a, b);
            break;
        case '-':
            subtract(a, b);
            break;
        case 'x':
            multiply(a, b);
            break;
        default:
            printf("Sample input: 12 + 34");
    }
    return 0;
}
