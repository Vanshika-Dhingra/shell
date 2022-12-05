#include "headers.h"

static int myCompare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void bubbleSort(const char *arr[], int n)
{
    qsort(arr, n, sizeof(const char *), myCompare);
}

void ls_l_func(char filename[])
{
    FILE *file;
    file = fopen(filename, "r");
    if (file)
    {
        struct passwd *usr;
        struct group *grp;
        int x;
        int tm_sec = 1;
        char *time;
        time=(char*)malloc(sizeof(char)*50);
        struct stat st = {0};
        stat(filename, &st);

        usr = getpwuid(st.st_uid);
        grp = getgrgid(st.st_gid);

        x = st.st_mode;
        if (S_ISDIR(x))
            printf("d");
        else if (S_ISREG(x))
            printf("-");

        (x & S_IRUSR) ? printf("r") : printf("-");
        (x & S_IWUSR) ? printf("w") : printf("-");
        (x & S_IXUSR) ? printf("x") : printf("-");
        (x & S_IRGRP) ? printf("r") : printf("-");
        (x & S_IWGRP) ? printf("w") : printf("-");
        (x & S_IXGRP) ? printf("x") : printf("-");
        (x & S_IROTH) ? printf("r") : printf("-");
        (x & S_IWOTH) ? printf("w") : printf("-");
        (x & S_IXOTH) ? printf("x ") : printf("- ");

        strftime(time, sizeof(time), "%b %d %H:%M", localtime(&st.st_mtime));

        printf("%d %s %s %d %s ", (int)st.st_nlink, usr->pw_name, grp->gr_name, (int)st.st_size, time);
        DIR *d;
        d = opendir(filename);
        if (d)
        {
            printf("\033[01;32m%s\033[01;00m\n", filename);
        }
        else if (S_IEXEC & x)
        {
            printf("\033[01;33m%s\033[01;00m\n", filename);
        }
        else
        {
            printf("\033[1;31m%s\033[0m\n", filename);
        }
        return;
        fclose(file);
    }
    else
    {
        perror(filename);
    }
}

void ls_func(char *path, int a)
{
    char *c[1000];
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    int i = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if ((dir->d_name[0] == '.') && a == 1)
            {
                printf("\033[01;32m%s\033[01;00m\n", dir->d_name);
            }
            else if ((dir->d_name[0] == '.') && a == 0)
            {
            }
            else
            {
                c[i] = dir->d_name;
                i++;
            }
        }
        closedir(d);
    }
    else
    {
        FILE *file;
        if ((file = fopen(path, "r")))
        {
            fclose(file);
            printf("\033[1;31m%s\033[0m\n", path);
        }
        else
        {
            perror(path);
        }
    }
    bubbleSort(c, i);
    for (int j = 0; j < i; j++)
    {
        DIR *di;
        di = opendir(c[j]);
        struct stat st = {0};
        stat(c[j], &st);

        int x = st.st_mode;
        if (di)
        {
            printf("\033[01;32m%s\033[01;00m\n", c[j]);
        }
        else if (S_IEXEC & x)
        {
            printf("\033[01;33m%s\033[01;00m\n", c[j]);
        }
        else
        {
            printf("\033[1;31m%s\033[0m\n", c[j]);
        }
    }
}

void ls_l(char *path, int a)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    printTotal(d, dir, path, a);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if ((dir->d_name[0] == '.') && a == 1)
            {
                ls_l_func(dir->d_name);
            }
            else if ((dir->d_name[0] == '.') && a == 0)
            {
            }
            else
            {
                ls_l_func(dir->d_name);
            }
        }
        closedir(d);
    }
    else
    {
        ls_l_func(path);
    }
}

void exec_ls(char *root, char *words[], int noOfArgs)
{
    char *ls_words[500];
    noOfArgs--;
    for (int l = 1; l <= noOfArgs; l++)
    {
        ls_words[l - 1] = words[l];
    }
    bubbleSort(ls_words, noOfArgs);
    int l = 0, a = 0;
    if (noOfArgs == 0)
    {
        char path[1024];
        getcwd(path, 1023);
        ls_func(path, 0);
    }
    for (int i = 0; i < noOfArgs; i++)
    {
        char *folder = NULL;
        char *filename = NULL;
        if (strcmp(ls_words[i], "-l") == 0)
        {
            l = 1;
        }
        else if (strcmp(ls_words[i], "-a") == 0)
        {
            a = 1;
        }
        else if (strcmp(ls_words[i], "-al") == 0 || strcmp(ls_words[i], "-la") == 0)
        {
            a = 1;
            l = 1;
        }
    }
    int i;
    int flag = 1;
    for (i = 0; i < noOfArgs; i++)
    {
        if (strcmp(ls_words[i], "-l") == 0 || strcmp(ls_words[i], "-a") == 0 || strcmp(ls_words[i], "-la") == 0 || strcmp(ls_words[i], "-al") == 0)
        {
            flag = 0;
        }
        else if (strcmp(ls_words[i], ".") == 0)
        {
            flag = 1;
            if (l == 1)
            {
                char path[1024];
                getcwd(path, 1023);
                ls_l(path, a);
            }
            else
            {
                char path[1024];
                getcwd(path, 1023);
                ls_func(path, a);
            }
        }
        else if (strcmp(ls_words[i], "..") == 0)
        {
            char temp[1024];
            getcwd(temp, 1023);
            chdir("..");
            char temp1[1024];
            getcwd(temp1, 1023);
            flag = 1;
            ls_func(temp1, a);
            chdir(temp);
        }
        else if (strcmp(ls_words[i], "~") == 0)
        {
            flag = 1;
            if (l == 1)
            {
                ls_l(root, a);
            }
            else
            {
                ls_func(root, a);
            }
        }
        else
        {
            flag = 1;
            DIR *d;
            d = opendir(ls_words[i]);
            if (d)
            {
                char path[1024];
                getcwd(path, 1023);
                strcat(path, "/");
                strcat(path, ls_words[i]);
                if (l == 1)
                {
                    char path1[1024];
                    getcwd(path1, 1023);
                    chdir(path);
                    ls_l(path, a);
                    chdir(path1);
                }
                else
                {
                    char path1[1024];
                    getcwd(path1, 1023);
                    chdir(path);
                    ls_func(path, a);
                    chdir(path1);
                }
            }
            else
            {
                if (l == 1)
                    ls_l_func(ls_words[i]);
                else
                {
                    ls_func(ls_words[i], a);
                }
            }
        }
    }
    if (flag == 0)
    {
        char path[1024];
        getcwd(path, 1023);
        if (l == 1)
            ls_l(path, a);
        else
            ls_func(path, a);
    }
    for (int k = 0; k < i - 1; k++)
    {
        ls_words[k] = NULL;
    }
}

void printTotal(DIR *d, struct dirent *dir, char path[], int a)
{
    long long total = 0;
    while ((dir = readdir(d)) != NULL)
    {
        if (dir->d_name[0] == '.' && a == 0)
        {
        }
        else
        {
            char temp[2048];
            strcpy(temp, path);
            strcat(temp, "/");
            strcat(temp, dir->d_name);
            struct stat directory = {0};
            if (stat(temp, &directory) == 0)
                total += directory.st_blocks;
        }
    }
    printf("total %lld\n", total);
    rewinddir(d);
    return;
}