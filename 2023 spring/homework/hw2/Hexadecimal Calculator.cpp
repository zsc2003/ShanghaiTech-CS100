#include<stdio.h>
#include<string.h>
#include<math.h>

char s1[60],s2[60], out[60];
int a[60], b[60], ans[60];
	
int main()
{
	char c;
	
	scanf("%c",&c);
	scanf("%s%s",s1,s2);
	
	int l1 = strlen(s1), l2 = strlen(s2);
	int len = l1>l2?l1:l2;
	
	//reverse + transfer
	for(int i = 0; i < l1; ++i)
	{
		if('0' <= s1[i] && s1[i] <= '9')
			a[l1 - i - 1] = s1[i] - '0';
		else
			a[l1 - i - 1] = s1[i] - 'a' + 10;
	}
	for(int i = 0; i < l2; ++i)
	{
		if('0' <= s2[i] && s2[i] <= '9')
			b[l2 - i - 1] = s2[i] - '0';
		else
			b[l2 - i - 1] = s2[i] - 'a' + 10;
	}
	
	if(c == '+')
	{
		for(int i = 0; i < len; ++i)
		{
			ans[i] += a[i] + b[i];
			ans[i + 1] += ans[i] / 16;
			ans[i] %= 16;
		}
	}
	else
	{
		for(int i = 0; i < len; ++i)
		{
			ans[i] += a[i] - b[i];
			if(ans[i] < 0)
			{
				--ans[i + 1];
				ans[i] += 16;
			}
		}
	}
	
	// It is guaranteed that L(r) <= max(L(a), L(b))
	printf(" ");
	for(int i = 1; i <= len - l1; ++i)
		printf(" ");
	printf("%s\n",s1);
	
	printf("%c",c);
	for(int i = 1; i <= len - l2; ++i)
		printf(" ");
	printf("%s\n",s2);
	
	for(int i = 1; i <= len + 1; ++i)
		printf("-");
	printf("\n");
	
	out[0] = ' ';
	for(int i = len - 1;i >= 0; --i)
	{
		if(0<=ans[i]&&ans[i]<=9)
			out[len - i] = ans[i] + '0'; 
		else
			out[len - i] = ans[i] - 10 + 'a'; 
	}
	out[len + 1] = '\0';
	int flag = 0;
	for(int i = 1; i <= len; ++i)
	{
		if(out[i] != '0')
		{
			flag = 1;
			break;
		}
		out[i] = ' ';
	}
	
	if (flag == 0)
		out[len] = '0';
	printf("%s", out);
	return 0;
}
