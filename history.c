#include"headers.h"

void exit_history(int flag, char *root, FILE *fptr, char ListOfHistory[][200], int d)
{
    chdir(root);
    fptr = fopen("history.txt", "w");
    if (flag == 1)
    {
        for (int i = 0; i < d + 1 && i < 20; i++)
        {
            fprintf(fptr, "%s", ListOfHistory[i]);
        }
        fclose(fptr);
    }
    if (flag == 0)
    {
        for (int i = 0; i < d && i < 20; i++)
        {
            fprintf(fptr, "%s", ListOfHistory[i]);
        }
        fclose(fptr);
    }
}

void write_history(FILE * fptr,char ListOfHistory[][200],int d,int i)
{
    char chunk[1000];
    fptr = fopen("history.txt", "r");
    int a = 0;
    i = 0;
    if (d >= 20 || (d < 20 && d > 10))
    {
        for (int j = 9; j >= 0; j--)
        {
            printf("%d %s", 10 - j, ListOfHistory[j]);
        }
    }
    else if (d < 10)
    {
        d++;
        for (int j = d - 1; j >= 0; j--)
        {
            printf("%d %s", d - j, ListOfHistory[j]);
        }
    }
}