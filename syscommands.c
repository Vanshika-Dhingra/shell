#include "headers.h"
int ret_fork;
struct bg temp_back;

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
        ret_fork=forkReturn;
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
            if ((temp_back.pid[i]) == 0)
            {
                temp_back.id[i]=temp_back.total+1;
                temp_back.pid[temp_back.total] = forkReturn;
                strcpy(temp_back.command[temp_back.total], words[0]);
                int k=1;
                while(words[k]!=NULL)
                {
                    strcat(temp_back.command[temp_back.total]," ");
                    strcat(temp_back.command[temp_back.total],words[k]);
                    k++;
                }
                temp_back.total++;
                printf("[%d] %d\n", i + 1, forkReturn);

                break;
            }
        }
    }
}