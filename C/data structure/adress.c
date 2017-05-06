#include <stdio.h>
int makenew(int B)
{
    printf("In makenew(),B的值为：%d,地址为：%p", B, &B);
}
int main()
{
    int A = 2;
    printf("In main(),A的值为：%d,地址为：%p\n", A, &A);
    makenew(A);
}
