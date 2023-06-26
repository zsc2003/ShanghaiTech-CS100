#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[25],bin[20];
int dp[25][25][25][25][3],cnt[5];
void pre(int n)
{//将除顺子,连对,3连对的情况用dp计算 
//dp[i][j][k][l][m] i个1张 j个2张 k个3张 l个4张 m个王的最少出牌数
	memset(dp,0x7f,sizeof(dp));
	dp[0][0][0][0][0]=0;
	for(int l=0;l<=n/4;++l)//循环顺序! 
		for(int k=0;k<=n/3;++k)
			for(int j=0;j<=n/2;++j)
				for(int i=0;i<=n;++i)
					for(int m=0;m<=2;++m)
					{
						int x=0x7f;
						if(i>0)x=min(x,dp[i-1][j][k][l][m]+1);
                        if(j>0)x=min(x,dp[i][j-1][k][l][m]+1);
                        if(k>0)x=min(x,dp[i][j][k-1][l][m]+1);
                        if(l>0)x=min(x,dp[i][j][k][l-1][m]+1);
                        if(m>0)x=min(x,dp[i][j][k][l][m-1]+1);
                        if(m>1)x=min(x,dp[i][j][k][l][m-2]+1);
						//3带1
                        if(i>0&&k>0)x=min(x,dp[i-1][j][k-1][l][m]+1);
                        if(m>0&&k>0)x=min(x,dp[i][j][k-1][l][m-1]+1); 
                        //3带2
                        if(j>0&&k>0)x=min(x,dp[i][j-1][k-1][l][m]+1);
                        //4带2
                        if(i>1&&l>0)x=min(x,dp[i-2][j][k][l-1][m]+1);
                        if(i>0&&l>0&&m>0)x=min(x,dp[i-1][j][k][l-1][m-1]+1);
                        if(l>0&&m>1)x=min(x,dp[i][j][k][l-1][m-2]+1);
                        if(j>0&&l>0)x=min(x,dp[i][j-1][k][l-1][m]+1);
                        if(j>1&&l>0)x=min(x,dp[i][j-2][k][l-1][m]+1);
                        if(l>1)x=min(x,dp[i][j][k][l-2][m]+1);
                        //拆牌 
                        if(l>0)x=min(x,dp[i+1][j][k+1][l-1][m]);
                        if(k>0)x=min(x,dp[i+1][j+1][k-1][l][m]);
                        dp[i][j][k][l][m]=min(dp[i][j][k][l][m],x);
					}
}
void dfs(int step,int *ans)
{//Bomb(炸弹)Trio(3个)Pair(1对)Solo(单) all invoved in count
	memset(cnt,0,sizeof(cnt));
	for(int i=3;i<=15;++i)
		cnt[bin[i]]++;
	cnt[5]=bin[16];
	if((*ans)>dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]]+step)
		(*ans)=dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]]+step;
	if(step>=(*ans))
		return;
	if(dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]]==0)
	{
		(*ans)=step;
		return;
	}
	int i; 
//-----------------------------------------------------------
	for(i=3;i<=14;++i)//Sequence of trios(三连对)
	{//without jokeres and twos
		int j=i,k;
		while(bin[j]>=3&&j<=14)
		{
			if(j-i+1>=2)
			{
				for(k=i;k<=j;++k)//以i为开头,j为结尾
					bin[k]-=3;
				dfs(step+1,ans);
				for(k=i;k<=j;++k)
					bin[k]+=3;
			}
			j++;
		}		
	}
//-----------------------------------------------------------
	for(i=3;i<=14;++i)//Sequence of pairs连对
	{//without jokeres and twos
		int j=i,k;
		while(bin[j]>=2&&j<=14)
		{
			if(j-i+1>=3)
			{
				for(k=i;k<=j;++k)//以i为开头,j为结尾 
					bin[k]-=2;
				dfs(step+1,ans);
				for(k=i;k<=j;++k)
					bin[k]+=2;
			}
			j++;
		}		
	}
//-----------------------------------------------------------
	for(i=3;i<=14;++i)//Sequence顺子 
	{//without jokeres and twos
		int j=i,k;
		while(bin[j]>=1&&j<=14)
		{
			if(j-i+1>=5)
			{
				for(k=i;k<=j;++k)//以i为开头,j为结尾 
					bin[k]--;
				dfs(step+1,ans);
				for(k=i;k<=j;++k)
					bin[k]++;
			}
			j++;
		}		
	}
}
int main()
{
	int T,n,f;
	scanf("%d%d",&T,&n);
	pre(n);
	while(T--)
	{
		memset(bin,0,sizeof(bin));
		int i;
		for(i=1;i<=n;++i)
		{
			scanf("%d%d",&a[i],&f);
			if(a[i]==1)a[i]=14;//A->14
			else if(a[i]==2)a[i]=15;//2->15
			else if(a[i]==0)a[i]=16;//joker->16
			bin[a[i]]++;
		}
		int ans=n;//the maximum steps is the number of the pokers
		dfs(0,&ans);
		printf("%d\n",ans);
	}
	return 0;
}
