#include<stdio.h>
#include<string.h>

enum JumpType {
    T, S, Lo, F, Lz, A
}a;

static double scoreTable[4][6] = { {0.4, 0.4, 0.5, 0.5, 0.6, 1.1},
                                   {1.3, 1.3, 1.7, 1.8, 2.1, 3.3},
                                   {4.2, 4.3, 4.9, 5.3, 5.9, 8.0},
                                   {9.5, 9.7, 10.5, 11.0, 11.5, 12.5} };

double Score(int rotations, enum JumpType type){
    if (rotations < 1 || rotations > 4){
        return -1;
    }
    return scoreTable[rotations - 1][type];
}

double calc(char *s)
{
	int rotations=0,l=strlen(s),i;
	int jump_type=0,error_type1=0,error_type2=0;
	for(i=0;i<l;i++)
	{
		if(isdigit(s[i]))
			rotations=rotations*10+s[i]-'0';
		else
			break;
	}
	//printf("rotations=%d , i=%d\n",rotations,i);
	if(rotations<=0||rotations>=5)return -1;
	if(i==l)return -1;
	if(s[i]=='T')
		jump_type=1;
	else if(s[i]=='S')
		jump_type=2;
	else if(s[i]=='L')
	{
		i++;
		if(i==l)return -1;
		if(s[i]=='o')
			jump_type=3;
		else if(s[i]=='z')
			jump_type=5;
		else
			return -1;		
	}
	else if(s[i]=='F')
		jump_type=4;	
	else if(s[i]=='A')
		jump_type=6;
	else
		return -1;
	i++;
	if(i==l)
		error_type1=0;
	else
	{
		if(s[i]=='q')
			error_type1=1;
		else if(s[i]=='<')
		{
			if((i+1)==l)
				error_type1=2;
			else
			{
				i++;
				if(s[i]=='<')
					error_type1=3;
				else
					return -1;
			}
		}
		else if(s[i]=='!')
			error_type1=4;
		else if(s[i]=='e')
			error_type1=5;
		else
			return -1;
		i++;
	}
	if(i!=l)
	{
		if(s[i]=='q')
		{
			i++;
			error_type2=1;	
		}
		else if(s[i]=='<')
		{
			i++;
			if(i==l)
				error_type2=2;
			else
			{
				if(s[i]=='<')
					error_type2=3;
				else
					return -1;
				i++;
			}
		}
		else
			return -1;
	}
	if(i!=l)
		return -1;
	if(error_type1==4||error_type1==5)
	{
		if((jump_type!=4)&&(jump_type!=5))
			return -1;
	}
	if(1<=error_type2&&error_type2<=3)
	{
		if(1<=error_type1&&error_type1<=3)
			return -1;
	}
	double flag=1.0;
	if(error_type1==2||error_type1==5)
		flag*=0.7;
	else if(error_type1==3)
		rotations--;
	if(error_type2==2)
		flag*=0.7;
	else if(error_type2==3)
		rotations--;
	double score=0;
	if(jump_type==1)
		score=Score(rotations,T);
	else if(jump_type==2)
		score=Score(rotations,S);
	else if(jump_type==3)
		score=Score(rotations,Lo);
	else if(jump_type==4)
		score=Score(rotations,F);
	else if(jump_type==5)
		score=Score(rotations,Lz);
	else if(jump_type==6)
		score=Score(rotations,A);	
	if(score+1.0<=1e-3)
		return 0;
	return score*flag;
}
int main()
{
//	freopen("debug.in","r",stdin);
//	printf("%.2lf\n\n\n\n",Score(1,T));
	int t,l,cnt;
	double flag,ans,val;
	for(t=0;t<3;++t)
	{
		flag=1.0;
		ans=0.0;
		char s[90];
		memset(s,0,sizeof(s));
		//gets(s);
		scanf("%s",s);
		l=strlen(s);
		if(s[l-1]=='+')
		{
			puts("0.00");
			continue;
		}
		int i;
		if(s[l-1]=='x')
		{
			flag=1.1;
			s[l-1]='+';
		}
		else
			s[l]='+';
		for(i=0;i<l-1;++i)
			if(s[i]=='+'&&s[i+1]=='+')
			{
				puts("0.00");
				flag=0;
				break;
			}
		if(flag<1e-3)
			continue;
		cnt=0;
		char *res=strtok(s,"+");//breaks a string into a sequence of tokens
		while(res!=NULL)
	    {
	    //	printf("%s\n",res);
	    	cnt++;
			val=calc(res);
	    	ans+=val;
	    	if(val+0.5<1e-3)
	    		flag=0;
			//printf("%.2lf\n",calc(res));
			res=strtok(NULL,"+");
		}
		if(cnt>3)
			ans=0;
		ans*=flag;
		if(ans<1e-3)
			ans=0.00;
		printf("%.2lf\n",ans);
	}
    return 0;
}//3Lze+3T+3Lzex
