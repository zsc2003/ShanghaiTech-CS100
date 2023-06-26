#include<stdio.h>
#include<string.h>
const int N=6010;
int check(char *s,int l,int r)
{
	char *s1=(char*)malloc(sizeof(char)*(r-l+1));
	int cnt=0,i;
	for(i=l;i<=r;i++)
	{
		if('a'<=s[i]&&s[i]<='z')
			s1[cnt++]=s[i];
		else if('A'<=s[i]&&s[i]<='Z')
			s1[cnt++]=s[i]-'A'+'a';
	}
	int len=cnt;
	cnt=len/2;
	for(i=0;i<cnt;i++)
		if(s1[i]!=s1[len-i-1])
		{
			free(s1);
			return 0;
		}
	free(s1);
	return 1;
}
int main()
{
	char s[N],s1[N],c;
	gets(s);
	//printf("%d\n",strlen(s));
	int n,opt,l,r,pos;
	scanf("%d",&n);
	while(n--)
	{
		//printf("%s\n",s);
		scanf("%d",&opt);
		if(opt==0)
		{	
			scanf("%d%d",&l,&r);
			if(check(s,l,r)==1)
				puts("Yes");
			else
				puts("No");
		}
		else if(opt==1)
		{
			scanf("%d",&pos);
			getchar();
			c=getchar();
			getchar();
			s[pos]=c;
		}
		else
		{
			gets(s1);
			strcat(s,s1+1);//去一个空格 		
		}		
	}
    return 0;
}
