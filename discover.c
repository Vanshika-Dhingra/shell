#include "headers.h"

void relpath(char *cwd, char *path)
{
    int len_cwd, len_path, min;
    len_path = strlen(path);
    len_cwd = strlen(cwd);
    min = len_path;
    int flag = 1;
    if (len_path > len_cwd)
        min = len_cwd;
    int i;
    for (i = 0; i < min; i++)
    {
        if (cwd[i] == path[i])
        {
        }
        else
        {
            flag = 0;
            break;
        }
    }
    char *relpat = NULL;
    relpat = (char *)malloc(sizeof(int) * 100);
    relpat[0] = '.';
    if (flag)
    {
        for (int j = i; j < strlen(path); j++)
        {
            relpat[1 + j - i] = path[j];
        }
    }
    strcpy(path, relpat);
}

void discover(char path[], int i, int j)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        if (j == 1)
        {
            char *copy;
            copy = (char *)malloc(100 * sizeof(int));
            strcpy(copy, path);
            char *pwd = NULL;
            char temp[1024];
            pwd = getcwd(temp, 1023);
            relpath(pwd, copy);
            printf("%s\n", copy);
        }
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                char str[1024];
                char str1[1024];
                strcpy(str, dir->d_name);
                strcpy(str1, path);
                strcat(str1, "/");
                strcat(str1, str);
                discover(str1, i, j);
            }
        }
        closedir(d);
    }
    else
    {
        if (i == 1)
        {
            char *pwd = NULL;
            char temp[1024];
            pwd = getcwd(temp, 1023);
            relpath(pwd, path);
            printf("%s\n", path);
        }
    }
}

void discover_file(char path[], char *filename)
{

    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                char str[1024];
                char str1[1024];
                strcpy(str, dir->d_name);
                strcpy(str1, path);
                strcat(str1, "/");
                strcat(str1, str);
                DIR *check;
                check = opendir(str1);
                if (check)
                {
                    discover_file(str1, filename);
                }
                
            }
        }
        closedir(d);
    }
    else
    {
    }
}

void exec_discover(char *root, char *words[], int noOfArgs)
{
    int d = 0, f = 0;
    char *folder = NULL;
    char *str = NULL;
    char *str1 = NULL;
    char *filename = NULL;
    for (int i = 1; i < noOfArgs; i++)
    {
        if (strcmp(words[i], "-d") == 0)
        {
            d = 1;
        }
        else if (strcmp(words[i], "-f") == 0)
        {
            f = 1;
        }
        else if (strcmp(words[i], ".") == 0 || strcmp(words[i], "..") == 0)
        {
            folder = (char *)malloc(100 * sizeof(char));
            strcpy(folder, words[i]);
        }
        else if (words[i][0] == '.' && words[i][1] != '\0')
        {
            str = (char *)malloc(100 * sizeof(char));
            for (int j = 1; j < strlen(words[i]); j++)
            {
                str[j - 1] = words[i][j];
            }
            folder = (char *)malloc(100 * sizeof(char));
            for (int j = 2; j < strlen(words[i]); j++)
            {
                folder[j - 2] = words[i][j];
            }
        }
        else if (strcmp(words[i], "~") == 0)
        {
            folder = (char *)malloc(100 * sizeof(char));
            strcpy(folder, "~");
        }
        else
        {
            DIR *d;
            d = opendir(words[i]);
            if (d)
            {
                folder = (char *)malloc(100 * sizeof(char));
                str = (char *)malloc(100 * sizeof(char));
                strcpy(folder, words[i]);
                strcpy(str, "/");
                strcat(str, folder);
            }
            else
            {
                filename = (char *)malloc(100 * sizeof(char));
                strcpy(filename, words[i]);
            }
        }
    }
    if (d == 0 && f == 0)
    {
        d = 1;
        f = 1;
    }
    if (filename == NULL && folder == NULL)
    {
        char *cwd4 = getcwd(str1, 1023);
        discover(cwd4, f, d);
    }
    else if (folder == NULL)
    {
        if (f == 1 || (d = 1 && f == 1))
        {
            char *cwd4 = getcwd(str1, 1023);
            discover_file(cwd4, filename);
        }
        else
        {
            printf("no such directory\n");
        }
    }
    else if (filename == NULL)
    {
        if (strcmp(folder, ".") == 0)
        {
            char *cwd1;
            cwd1 = (char *)malloc(100 * sizeof(char));
            cwd1 = getcwd(str, 1023);
            discover(cwd1, f, d);
        }
        else if (strcmp(folder, "..") == 0)
        {
            char *cwd2;
            cwd2 = (char *)malloc(100 * sizeof(char));
            cwd2 = getcwd(str1, 1023);
            chdir("..");
            char *cwd1;
            cwd1 = (char *)malloc(100 * sizeof(char));
            cwd1 = getcwd(str, 1023);
            discover(cwd1, f, d);
            chdir(cwd2);
        }
        
        else
        {
            char str2[1024];
            char *cwd3 = getcwd(str2, 1023);
            strcat(cwd3, str);
            discover(cwd3, f, d);
        }
    }
    else
    {
        if (strcmp(folder, ".") == 0)
        {
            char *cwd1;
            cwd1 = (char *)malloc(100 * sizeof(char));
            cwd1 = getcwd(str, 1023);
            discover_file(cwd1, filename);
        }
       
        else
        {
            char str2[1024];
            char *cwd3 = getcwd(str2, 1023);
            strcat(cwd3, str);
            discover_file(cwd3, filename);
        }
    }
}
