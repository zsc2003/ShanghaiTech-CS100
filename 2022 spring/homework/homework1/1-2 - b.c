#include<stdio.h>
#include<math.h>

struct node
{
	int team;
	double x,y,dis;
}a[10];

const double r=1.8000000;//1.2ÄÜ¹ý??? 
int main()
{
	int i,ans=0;
	char c;
    for(i=1;i<=6;i++)
    {
    	//scanf("(%lf,%lf)",&a[i].x,&a[i].y);
    	c=getchar();
    	scanf("%lf",&a[i].x);
    	c=getchar();
    	scanf("%lf",&a[i].y);
    	c=getchar();
    	c=getchar();
		a[i].dis=sqrt(a[i].x*a[i].x+a[i].y*a[i].y);
		if(i<=3)a[i].team=1;
		else a[i].team=2;
	}
	//for(i=1;i<=6;i++)printf("%lf %lf %lf\n",a[i].x,a[i].y,a[i].dis);
	int j;
	for(i=1;i<=6;i++)
		for(j=i+1;j<=6;j++)
			if(a[i].dis>a[j].dis)
			{
				struct node f=a[i];
				a[i]=a[j];
				a[j]=f;
			}
	//for(i=1;i<=6;i++)printf("%lf %lf %lf %d\n",a[i].x,a[i].y,a[i].dis,a[i].team);
    if(a[1].dis>r)
    {
    	printf("BLANK END\n");
    	return 0;
	}
	ans=0;
	int win=a[1].team;
	for(i=1;i<=6;i++)
	{
		if((a[i].team==win)&&(a[i].dis<r))
			ans++;
		else
			break;
	}
	if(a[1].team==1)
	{
		printf("RED SCORES %d\n",ans);
		return 0;
	}
	printf("YELLOW SCORES %d\n",ans);
	return 0;
}/*
(-0.2,-0.2)
(-0.1,0.1)
(0.5,0.5)
(0.1,0.15)
(0.15,-0.5)
(0.5,-0.1)

(-0.2,-0.2)
(0.1,0.15)
(-0.1,0.1)
(0.5,0.5)
(0.15,-0.5)
(0.5,-0.1)
*/
