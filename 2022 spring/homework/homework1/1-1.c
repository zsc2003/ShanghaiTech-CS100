#include<stdio.h> 
int main()
{
    int a, b, c; // Store the number of students in classes A, B, and C.

    printf("How many students are in classes A, B, and C, respectively?\n");
    scanf("%d %d %d", &a, &b, &c);

	int maxn;
    if(a >= b && a >= c)
    {
    	maxn = a;
        printf("Class A has the most students, ");
	}
        
    else if(b >= a && b >= c)
    {
    	maxn = b;
        printf("Class B has the most students, ");
	}
        
    else if(c >= a && c >= b)
    {
    	maxn = c;
        printf("Class C has the most students, ");
	}
        
    
    int total = a + b + c + 1;

    // A class can accept at most half of all students. 
    if(maxn > total / 2)
        printf("and is overly enrolled!\n");
    if(maxn == total / 2)
        printf("and is full!\n");
    if(maxn < total / 2)
        printf("and still has open seats!\n");

    return 0;
}
