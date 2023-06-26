#include<stdio.h>
#include<string.h>
const int N=90;
char *delete_front(char *s)
{
	char *p=s;
	int l=0;
	while(*p==' '||*p=='\t')
	{
		++l;
		++p;
	}
	memmove(s,p,strlen(s)-l+1);
	return s;
}
char *delete_back(char *s)
{
	int len=strlen(s);
	char *p=s+len-1;
	while(p>=s&&(*p==' '||*p=='\t'))
	{
		*p='\0';
		--p;
	}
	return s;
}
int main()
{
//	freopen("debug.in","r",stdin);
//	freopen("debug.out","w",stdout);
	int n,len;
	char ss[N];
	scanf("%d",&n);
	getchar();
	int tab=0;
	while(n--)
	{
		gets(ss);
		char *s=delete_front(ss);
		s=delete_back(s);
		//printf("\n--------------------\n%s\n%d\n---------------------\n",s,strlen(s));
		len=strlen(s);
		int i;		
		if(s[len-1]=='{')
		{
			for(i=1;i<=tab;++i)
				printf("    ");
			++tab;
			char *s1=strtok(s,"{");//breaks a string into a sequence of tokens
			printf("%s {\n",delete_back(s1));
			continue;
		}
		if(s[0]=='}')
		{
			--tab;
			for(i=1;i<=tab;++i)
				printf("    ");
			puts(s);
			continue;
		}
		char *res=strtok(s,";");//breaks a string into a sequence of tokens
		while(res!=NULL)
	    {
			for(i=1;i<=tab;++i)
				printf("    ");
			printf("%s;\n",delete_front(res));//delete the space in front of the string
			res=strtok(NULL,";");
		}		
	}
    return 0;
}
