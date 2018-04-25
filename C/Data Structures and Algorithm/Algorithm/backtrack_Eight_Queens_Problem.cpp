/*
	八皇后问题：回溯法
	create by Ian in 2018-1-2 21:49:28

	变量描述：
		i：皇后的下标
		x[i]：第i个皇后选择的列号
		n：皇后总数
		k：皇后的序号，第k个皇后

*/
#include <iostream>
#include <cmath>
using namespace std;


int x[20];

bool Place(int k, int i)
{
	// 能否放置一个新的皇后
	// 第k个皇后，在第i列是否可以放置
	for(int j=1; j<k; j++)
		if( x[j] == i ||  abs(x[j]-i) == abs(j-k) )
			return false;
	return true;
}

void NQueens(int k, int n)
{
	// 输出n皇后的所有解
	for(int i=1; i<=n; i++)
	{
		if(Place(k,i))
		{
			x[k] = i;
			if(k==n)
			{
				for(int j=1; j<=n; j++)
					cout << x[j] << " ";
			}
			else NQueens(k+1, n);
		}
	}
}

int main(int argc, char const *argv[])
{
	int k,n;
	cin >> k >> n;
	for(int i=0; i<n; i++) x[i] = 0;
	NQueens(k, n);
	return 0;
}