#include<stdio.h>
#include<math.h>

typedef double db;

int main()
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	
	if(a == 0)
	{
		if(b == 0)
		{
			if(c == 0)
			{
				puts("x\\in\\mathbb{R}");
				return 0;
			}
			puts("No solution.");
			return 0;
		}
		printf("x = %.3lf\n", (db)(-c) / (db)b);
		return 0;
	}
	
	int delta = b*b - 4*a*c;
	if(delta < 0)
	{
		puts("No solution.");
		return 0;
	}
	db sqr = sqrt(delta);
	
	if(a < 0)
		sqr = -1.0000 * sqr;
	
	db x1 = (-(db)b - sqr) / (db)2.0 / (db)a;
	db x2 = (-(db)b + sqr) / (db)2.0 / (db)a;
	if(delta == 0)
		printf("x1 = x2 = %.3lf\n", x1);
	else
		printf("x1 = %.3lf, x2 = %.3lf\n", x1, x2);
	return 0;
}
