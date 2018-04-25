/*
	2017年6月25日11:12:35
	使用栈来检测字符串是否为回文
	步骤:
	1. 输入一个字符串
	2. 取字符串中间值下标
	3. 将中间值以及之前的值按顺序入栈
	4. 找到中间值后第一个需要匹配的字符下标
	5. 栈中的值与中间值后的值依次匹配，当一个字符匹配不成功或匹配完成就跳出
	6. 判断是否为回文，如果栈没弹空，则不是回文
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Max 101

int main()
{
	char a[Max], s[Max];
	int i, len, mid, next, top;

	gets(a);
	len = strlen(a);
	mid = len/2 -1;

	top = 0;// 栈初始化
	for(i=0; i<=mid; i++) // 字符入栈
		s[++top] = a[i];

	// 判断字符串长度是奇数还是偶数，找出需要进行匹配的字符下标
	if (len%2 == 0)
		next = mid+1;
	else
		next = mid+2;
	
	for(i=next; i<=len-1; i++)
	{
		if(a[i]!=s[top])
			break;
		top--;
	}

	if(top == 0)
		printf("Yes\n");
	else
		printf("No\n");
	system("pause");
	return 0;
}