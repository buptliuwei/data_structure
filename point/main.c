#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 100, b = 99, temp;
    int *pa = &a, *pb = &b;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
    printf("a=%d,b=%d\n", a,b);
    return 0;
}
