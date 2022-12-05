#include "headers.h"

char *relativePath(char *root, char *cwd)
{
    int len_cwd, len_root, min;
    len_cwd = strlen(cwd);
    len_root = strlen(root);
    min = len_cwd;
    int flag = 1;
    if (len_cwd > len_root)
        min = len_root;
    int i;
    for (i = 0; i < min; i++)
    {
        if (cwd[i] == root[i])
        {
        }
        else
        {
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        for (i = len_root; i <= len_cwd; i++)
            cwd[i - len_root + 1] = cwd[i];
        cwd[0] = '~';
        cwd[i] = '\0';

        return cwd;
    }
    else
        return cwd;
}

void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void display(struct bg *back, char *root, char *hostname)
{
    char temp[1024];
    char *user = NULL;
    char *pwd = NULL;
    uid_t uid = geteuid();
    struct passwd *sys_uid = getpwuid(uid);
    user = sys_uid->pw_name;

    getcwd(temp, 1023);
    pwd = relativePath(root, temp);

    int bg_status;
    for (int i = 0; i < 100; i++)
    {
        if (back->pid[i]>0)
        {
            char temp3[1024];
            if (waitpid(back->pid[i], &bg_status, WNOHANG) > 0)
            {
                int exit_status = WEXITSTATUS(bg_status);
                if(exit_status==0)
                {
                    strcpy(temp3,"normally");
                }
                else
                {
                    strcpy(temp3,"abnormally");
                }
                printf("%s with PID %d exited %s\n", back->command[i], back->pid[i],temp3);

                back->pid[i] = 0;
            }
        }
    }
    if (diff >= 1)
        printf("<%s@%s:%stook %llds>", user, hostname, pwd, diff);
    else
        printf("<%s@%s:%s>", user, hostname, pwd);
}