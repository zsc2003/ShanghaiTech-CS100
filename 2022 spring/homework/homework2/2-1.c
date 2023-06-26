#include <stdio.h>
#include <stdlib.h>

void merge(int x,int mid,int y,int *a)
{
	int k=0;
	int *p=(int*)malloc(sizeof(int)*(y-x+1));
	int l=x,r=mid+1;
	while(l<=mid&&r<=y)
	{
		if((*(a+l))<=(*(a+r)))
			p[k++]=*(a+(l++));
		else
			p[k++]=*(a+(r++));
	}
	while(l<=mid)
		p[k++]=*(a+(l++));
	while(r<=y)
		p[k++]=*(a+(r++));
	int i;
	for(i=0;i<k;++i)
		*(a+x+i)=*(p+i);
	free(p);
}

void mergesort(int x,int y,int *a)
{
	if(x==y)
		return;
	int mid=(x+y)>>1;
	mergesort(x,mid,a);
	mergesort(mid+1,y,a);
	merge(x,mid,y,a);	
}
void FindSecondMaxAndMin(int numbers[], int size, int* secondMax, int* secondMin)
{
	int i,j,f;
    /*for(i=0;i<size;++i)
    	for(j=i+1;j<size;++j)
			if(numbers[i]>numbers[j])
			{
				f=numbers[i];
				numbers[i]=numbers[j];
				numbers[j]=f;
			}*/
	mergesort(0,size-1,numbers);
	*secondMin=numbers[1];
	*secondMax=numbers[size-2];
	return;
}

#define SIZE 8

int main()
{
    int secondMax, secondMin;
    int numbers[SIZE] = {2, 3, 4, 7, 6, 10, 9, 8};
    FindSecondMaxAndMin(numbers, SIZE, &secondMax, &secondMin);
    printf("%d %d\n", secondMax, secondMin);
    return 0;
}
