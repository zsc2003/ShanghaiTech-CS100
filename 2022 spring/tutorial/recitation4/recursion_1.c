#include<stdio.h>

//Recursive
int Kakutani(int number) 
{
	int step=0;//Define and initialize integer variables, operation steps
	int s;//Define a temporary variable to store the number of steps in the intermediate process
	printf("%d ",number);
	step++;
   //Recursive exit, always get natural value 1
	if(number==1) 
	{
		return step;//return the number of steps
	}
	else 
	{
 
		if(number%2==0)//If it is an even number, divide by 2
		{  
			
			number/=2;
			s=Kakutani(number);
			step+=s;
			return step;//return the number of calculation steps
		}
		else 
		{    
			number=number*3+1;
			s=Kakutani(number);
			step+=s;
			return step;//return the number of calculation steps
		}
	}
}

int main()
{
    int step=Kakutani(22);
    printf("\n%d\n",step);
    return 0;
}