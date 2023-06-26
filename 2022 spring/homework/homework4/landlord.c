#include<stdio.h>
#include<string.h>
int a[20],bin[20];
int count()
{
	int num=0;
	int i;
	for(i=3;i<=16;++i)
		if(bin[i])
			num++;
	return num;
}
void dfs(int step,int *ans)
{//Bomb(炸弹)Trio(3个)Pair(1对)Solo(单) all invoved in count
	int greedy=count();
	if((*ans)>greedy+step)
		(*ans)=greedy+step;
	if(step>=(*ans))
		return;
	if(greedy==0)
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
//-----------------------------------------------------------	
	for(i=3;i<=15;++i)//Quad with 2 attached pairs(4带2对)
	{
		if(bin[i]>=4)
		{
			int j,k;
			for(j=3;j<=15;++j)//without jokeres
			{
				if(i==j)continue;
				if(bin[j]<2)continue;
				for(k=j+1;k<=15;++k)//without jokeres
				{//j,k must be different!!! 
					if(i==k)continue;
					if(bin[k]<2)continue;
					bin[i]-=4;
					bin[j]-=2,bin[k]-=2;
					dfs(step+1,ans);
					bin[i]+=4;
					bin[j]+=2,bin[k]+=2;
				}
			}
		}
	}
//-----------------------------------------------------------
	for(i=3;i<=15;++i)//Quad with 2 attached cards(4带2)
	{
		if(bin[i]>=4)
		{
			int j,k;
			for(j=3;j<=16;++j)//with joker
			{
				if(i==j)continue;
				if(bin[j]<1)continue;
				for(k=j+1;k<=16;++k)
				{//j,k must be different!!!
					if(i==k)continue;
					if(bin[k]<1)continue;
					bin[i]-=4;
					bin[j]--,bin[k]--;
					dfs(step+1,ans);
					bin[i]+=4;
					bin[j]++,bin[k]++;
				}
			}
		}
	}
//-----------------------------------------------------------
	for(i=3;i<=15;++i)//Trio with an attached pair(3带2)
	{
		if(bin[i]>=3)
		{
			int j;
			for(j=3;j<=15;++j)
			{
				if(i==j)continue;
				if(bin[j]<2)continue;
				bin[i]-=3;
				bin[j]-=2;
				dfs(step+1,ans);
				bin[i]+=3;
				bin[j]+=2;
			}
		}
	}
//-----------------------------------------------------------
	for(i=3;i<=15;++i)//Trio with an attached card(3带1)
	{
		if(bin[i]>=3)
		{
			int j;
			for(j=3;j<=16;++j)
			{
				if(i==j)continue;
				if(bin[j]<1)continue;
				bin[i]-=3;
				bin[j]--;
				dfs(step+1,ans);
				bin[i]+=3;
				bin[j]++;
			}
		}
	}
}
int main()
{
	int T,n;
	scanf("%d%d",&T,&n);
	while(T--)
	{
		memset(bin,0,sizeof(bin));
		int i;
		for(i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			if(a[i]==1)a[i]=14;//A->14
			else if(a[i]==2)a[i]=15;//2->15
			else if(a[i]==14)a[i]=16;//joker->16
			bin[a[i]]++;
		}
		int ans=n;//the maximum steps is the number of the pokers
		dfs(0,&ans);
		printf("%d\n",ans);
	}
	return 0;
}
