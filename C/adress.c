#include <stdio.h>
int makenew(int B)
{
    printf("In makenew(),B��ֵΪ��%d,��ַΪ��%p", B, &B);
}
int main()
{
    int A = 2;
    printf("In main(),A��ֵΪ��%d,��ַΪ��%p\n", A, &A);
    makenew(A);
}
