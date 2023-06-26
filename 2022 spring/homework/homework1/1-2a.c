#include<stdio.h> 
int main()
{
    int n;
    scanf("%d",&n);
    double t,f,ans=0.00,a,v,las;
    char s1[110],s[110];
    las=0.00000;
    v=3.00000;
    a=-0.200000;
	while(n--)
	{
		scanf("%lf%s%s",&f,s1,s+1);
		//printf("%s\n",s+1);
		//printf("%c\n",s[1]);
		t=f-las;
		if(v<1e-3)continue;
		if(v+a*t<1e-3)
		{
			t=-v/a;
			ans+=v*t+a*t*t/2.0000000;
			v=-1e9;
			continue;
		}
		ans+=v*t+a*t*t/2.0000000;
		v+=a*t;
		if(s[1]=='H')
			a=-0.100000;
		else
			a=-0.200000;
		las=f;
	}
	if(v>1e-3)
	{
		t=-v/a;
		ans+=v*t+a*t*t/2.0000000;
	}
	printf("The stone has slided for %.3lfm\n",ans);
    return 0;
}/*
2
1.00 - H
2.00 - W
*/
