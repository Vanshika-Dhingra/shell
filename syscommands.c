#include "headers.h"

void foreGround(char *words[])
{
    pid_t forkReturn = fork();
    if (forkReturn < 0)
    {
        perror("error in forking");
    }
    else if (forkReturn == 0)
    {
        int a = execvp(words[0], words);
        if (a < 0)
        {
            perror("error in execvp");
        }
    }
    else
    {
        int fg_status;
        time_t start = time(NULL);
        int t = waitpid(forkReturn, &fg_status, WUNTRACED);
        if (t < 0)
        {
            perror("error in waitpid");
        }
        time_t end = time(NULL);
        diff += end - start;
    }
}

void backGround(char *words[], struct bg *back)
{
    pid_t forkReturn = fork();
    if (forkReturn < 0)
    {
        perror("error in forking");
    }
    else if (forkReturn == 0)
    {
        int t = setpgid(0, 0);
        if (t < 0)
        {
            perror("error in setpgid");
        }
        int a = execvp(words[0], words);
        if (a < 0)
        {
            perror("error in execvp");
        }
    }
    else
    {
        for (int i = 0; i < 100; i++)
        {
            if ((back->pid[i]) == 0)
            {
                back->pid[i] = forkReturn;
                strcpy(back->command[i], words[0]);
                printf("[%d] %d\n", i + 1, forkReturn);
                break;
            }
        }
    }
}