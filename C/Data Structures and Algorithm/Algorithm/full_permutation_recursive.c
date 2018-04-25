/*实现数字的全排列：递归算法
	create by Ian begin in 2017-9-23 15:11:22
*/
#include <stdio.h>
#include <stdlib.h>
#define Max 100
int n = 0;


void swap(int *a, int *b)
{
    /* 调转数组的两个值*/
    int m;
    m = *a;
    *a = *b;
    *b = m;
}
void perm(int list[], int k, int m)
{
    /* 递归算法实现全排列 */
    int i;
    if(k > m)
    {
        for(i = 0; i <= m; i++)
            printf("%d ", list[i]);
        printf("\n");
        n++;
    }
    else
    {
        for(i = k; i <= m; i++)
        {
            swap(&list[k], &list[i]);
            perm(list, k + 1, m);
            swap(&list[k], &list[i]);
        }
    }
}


int main()
{
    int len = 0, i = 0;
    int list[Max];
	printf("=============permutation:recursive=============\n");
    printf("Please print the length of number(<=100):\n");
    scanf("%d",&len);
    while(len>100)
    {
        printf("Please enter again:\n");
        scanf("%d",&len);
    }
    printf("Please print the number:\n");
    for(i; i<len; i++)
        scanf("%d",&list[i]);
    
    perm(list, 0, len-1);
    printf("total:%d\n", n);
    getchar();
    return 0;
}