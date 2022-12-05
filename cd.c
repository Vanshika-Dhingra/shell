#include"headers.h"

void exec_cd(char * words[],char * prev_path1,char * prev_path,char * root,int noOfArgs)
{
    if(noOfArgs>2)
    {
        printf("error:Too many arguments\n");
        return;
    }
    if (strcmp(words[1], "-") == 0)
    {
        if(strcmp(prev_path,"a")==0)
        {
            printf("cd: OLDPWD not set\n");
            return;
        }
        getcwd(prev_path1, 1023);
        chdir(prev_path);
        printf("%s\n", prev_path);
        strcpy(prev_path, prev_path1);
    }
    else
    {
        getcwd(prev_path, 1023);
        if (words[1] == NULL || strcmp(words[1], "~") == 0)
        {
            chdir(root);
        }
        else if(strcmp(words[1], "~/") == 0)
        {
            chdir(root);
        }
        else
        {
            DIR * d;
            d=opendir(words[1]);
            if(d)
            {
            chdir(words[1]);
            }
            else
            {
                perror(words[1]);
            }
        }
    }
}