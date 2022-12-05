#include "headers.h"

long long int diff;

int main()
{
    struct bg *back;
    back=(struct bg*)malloc(sizeof(struct bg));
    char *token;
    char *words[512];
    int noOfArgs;
    int tag_b;
    char command1[1024];

    char ListOfHistory[20][200];
    FILE *fptr;
    char chunk1[1000];
    fptr = fopen("history.txt", "r");
    int d = 0;
    while (fgets(chunk1, sizeof(chunk1), fptr) != NULL)
    {
        strcpy(ListOfHistory[d], chunk1);
        d++;
    }
    fclose(fptr);

    char ListOfcommands[1000][1000];
    char root[1024];
    getcwd(root, 1023);
    int p = 0;
    char hostname[100];
    gethostname(hostname, 100);
    char prev_path[1024]="a";
    char prev_path1[1024];

    while (1)
    {
        int i, j;
        display(back,root, hostname);
        diff = 0;
        char *line = NULL;
        size_t buffersize = 0;
        getline(&line, &buffersize, stdin);

        int flag = 1;
        if (strcmp(line, ListOfHistory[0]) == 0)
        {
            flag = 0;
        }
        if (flag == 1)
        {
            for (int i = d - 1; i >= 0; i--)
            {
                strcpy(ListOfHistory[i + 1], ListOfHistory[i]);
            }
            strcpy(ListOfHistory[0], line);
        }
        strcpy(ListOfcommands[p], line);
        if (strcmp(line, "cd\n") == 0)
        {
            chdir(root);
            if (flag == 1)
            {
                d++;
            }
            p++;
            continue;
        }
        char *commands[1000];
        char *command = strtok(line, ";");
        commands[0] = command;
        int z = 1;
        while (command != NULL)
        {
            command = strtok(NULL, ";");
            commands[z] = command;
            z++;
        }
        for (int y = 0; commands[y] != NULL; y++)
        {
            int count = 0;
            for (int i = 0; i < strlen(commands[y]); i++)
            {
                if (commands[y][i] == '&')
                    count++;
            }
            char *commands_[1000];
            char *command_ = strtok(commands[y], "&");
            commands_[0] = command_;
            int c = 1;
            while (command_ != NULL)
            {
                command_ = strtok(NULL, "&");
                commands_[c] = command_;
                c++;
            }

            for (int x = 0; commands_[x] != NULL; x++)
            {
                tag_b = 1;
                if (c - 2 == count)
                {
                    if (x == c - 2)
                    {
                        tag_b = 0;
                    }
                }
                char *word = strtok(commands_[x], " \t\r\n\a");
                words[0] = word;
                z = 1;
                while (word != NULL)
                {
                    word = strtok(NULL, " \t\r\n\a");
                    words[z] = word;
                    z++;
                }
                noOfArgs = z - 1;

                if (words[0] != NULL)
                {
                    if (strcmp(words[0], "cd") == 0)
                    {
                        exec_cd(words, prev_path1, prev_path, root,noOfArgs);
                    }
                    else if (strcmp(words[0], "echo") == 0)
                    {
                        echo_func(words, noOfArgs + 1);
                    }
                    else if (strcmp(words[0], "pwd") == 0)
                    {
                        pwd_func();
                    }
                    else if (strcmp(words[0], "ls") == 0)
                    {
                        exec_ls(root, words, noOfArgs);
                    }
                    else if (strcmp(words[0], "history") == 0)
                    {
                        write_history(fptr, ListOfHistory, d, i);
                    }
                    else if (strcmp(words[0], "exit") == 0)
                    {
                        exit_history(flag, root, fptr, ListOfHistory, d);
                        return 0;
                    }
                    else if (strcmp(words[0], "discover") == 0)
                    {
                        exec_discover(root, words, noOfArgs);
                    }
                    else if (strcmp(words[0], "pinfo") == 0)
                    {
                        func_pinfo(root, words[1], i - 1);
                    }
                    else
                    {
                        if(tag_b==0)
                        foreGround(words);
                        else
                        backGround(words,back);
                    }
                }
            }
        }
        if (flag == 1)
        {
            d++;
        }
        p++;
    }

    return 0;
}
