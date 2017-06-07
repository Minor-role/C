#include <stdio.h>

int akm(int m, int n)
{
	if(m==0)
		return n + 1;
	else if(m != 0 && n == 0)
		return akm(m-1, 1);
	else if(m != 0 && n != 0)
		return akm(m-1, akm(m, n-1));
	else 
		printf("error!\n");
	return 0; 
}

int main()
{
	/* code */
	int m, n;
	int temp = 0;
	printf("请输入m：\n");
	scanf("%d",&m);
	printf("请输入n：\n");
	scanf("%d",&n);
	temp = akm(m, n);
	printf("值为：%d",temp);
	return 0;
}
