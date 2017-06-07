/*
	2017年4月27日16:16:30
	创建一个顺序表，存放在数组 A[N]中，元素的类型为整型，设计算法调整A，
	使其左边的所有元素小于 0，右边的所有元素大于 0（要求算法的时间复杂度和空 间复杂度均为 O(n)）。
*/
#include <stdio.h>
#include <windows.h>
#define n 500
//test number:0 34 34 83 -34 -345 324 0 34 0 10086   
int change(int A[],int flag,int i)
{
	int j = 0;      //lift subscript
	int temp,i_temp;
	i_temp = i;
	while(j<i)
	{
		while(A[j] < flag && j<i)j++;
		while(A[i] > flag && j<i)i--;
		while(A[j] == flag && A[i] == flag)i--;
		if(j < i)
		{
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	i =  i_temp;
	while(j < i)
	{
		while(A[j] <= flag && j<i)j++;
		while(A[i] != flag && j<i )i--;
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
	int flag = 0;	 //flag  subscript
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
	system("pause");
	return 0;
}


