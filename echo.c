#include"headers.h"

void echo_func(char *words[],int j)
{
    int i = 1;

    while (i<j-1)
    {
        printf("%s ", words[i]);
        i++;
    }
    printf("\n");
}