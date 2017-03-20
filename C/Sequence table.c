#include<stdio.h>
#define n 500
//test number:1 2 0 -1 5 -3 -4 -5 10086
int change(int A[],int flag,int i)
{
	int j = 0;      //lift subscript
	int temp;
	while(j<i)
	{
		while(A[j] < flag && j<i)j++;
		while(A[i] > flag && j<i)i--;
		if(j < i)
		{
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
}

int main()
{
	int A[n]; //Array used to save the sequence table
	int x;    //To save the input number
	int i = 0;    //subscript
	int flag;	 //flag  subscript
	scanf("%d",&x);
	while(x != 10086)  // 10086 is exit flag
	{
		A[i] = x;	
		i++;
		scanf("%d",&x);
	}
	change(A,flag,i-1);   //in order to fix the bug
	printf("result:");
	for(flag = 0;flag < i;flag++) 
		printf(" %d ",A[flag]);
}


