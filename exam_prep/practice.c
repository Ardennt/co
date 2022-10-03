#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

void main()
{
    int i = 0;
    for (;i < 10; i++){
        printf("%d ", i);
    }
    printf("\n");
    printf("%d", i);
}