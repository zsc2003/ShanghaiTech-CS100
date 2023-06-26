#include<stdio.h>

int main()
{
	int n;
	char c;
    scanf("%d", &n);
	getchar();
    n = -n;
    while(1)
    {
    	scanf("%c", &c);
    	if('A' <= c && c <= 'Z')
		{
			c = 'A' + (c - 'A' + n % 26 + 26) % 26;
		}
		else if('a' <= c && c <= 'z')
		{
			c = 'a' + (c - 'a' + n % 26 + 26) % 26;
		}
		else if('0' <= c && c <= '9')
		{
			c = '0' + (c - '0' + n % 10 + 10) % 10;
		}
		printf("%c",c);
		if(c == '\n')
		{
			break;
		}
	}
    return 0;
}
