#include <stdio.h>

char* s1[20]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
char* s2[10]={"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety","hundred","thousand"};
	
void hundred(int n)
{
	if(n<20)
	{
		printf("%s",s1[n]);
		return;
	}
	if(n%10==0)
	{
		printf("%s",s2[n/10-2]);
		return;
	}
	printf("%s-%s",s2[n/10-2],s1[n%10]);
	return;
}

void thousand(int n)
{
	if(n%100==0)
	{
		printf("%s hundred",s1[n/100]);
		return;
	}
	printf("%s hundred and ",s1[n/100]);
	hundred(n%100);
	return;
}

void million(int n)
{
	if(n/1000<100)
		hundred(n/1000);
	else
		thousand(n/1000);
	printf(" thousand");
	if(n%1000==0)
		return;
	if(n%1000<100)
	{
		printf(" and ");
		hundred(n%1000);
		return;
	}
	printf(" ");
	thousand(n%1000);
	return;
}

int main()
{
	int n;
	scanf("%d",&n);
	
	if(n<100)
		hundred(n);
	else if(n<1000)
		thousand(n);
	else
		million(n);
	return 0;
}
