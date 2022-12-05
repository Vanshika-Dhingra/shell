#include "headers.h"

long long int diff;
extern struct bg temp_back;

int exec_pipe(char *pipeBef[], char *words[], char prev_path[], char prev_path1[], char root[], int noOfArgs, FILE *fptr, char *ListOfHistory[], int d, int i, int flag, int tag_b, struct bg *back, struct bg_final back_final[])
{
    int pip[2];
    int ret_val1 = 1;
    int index_pipe = -1;
    int j;
    for (j = 0; j < noOfArgs; j++)
    {
        if (strcmp(words[j], "|") == 0)
        {
            index_pipe = j;
            break;
        }
    }

    if (index_pipe == -1)
    {
        //////////////////////////////////////////////////////////////
        int stdincpy = dup(0);
        dup2(pip[0], 0);
        int out;
        char filen[1024];

        int check = 0;
        for (int i = 0; i < noOfArgs; i++)
        {
            if (strcmp(words[i], ">") == 0)
            {
                strcpy(filen, words[i + 1]);
                out = open(words[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                check = 1;
                for (int j = i; j < noOfArgs; j++)
                {
                    words[j] = NULL;
                }
                noOfArgs = i;
                break;
            }
            else if (strcmp(words[i], ">>") == 0)
            {
                strcpy(filen, words[i + 1]);
                out = open(words[i + 1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                check = 1;
                for (int j = i; j < noOfArgs; j++)
                {
                    words[j] = NULL;
                }
                noOfArgs = i;
                break;
            }
        }
        int stdoutCopy;
        if (check != 0)
        {
            stdoutCopy = dup(1);
            dup2(out, 1);
        }

        int ret_val = exec(words, prev_path, prev_path1, root, noOfArgs, fptr, ListOfHistory, d, i, flag, tag_b, back, back_final);
        if (ret_val == 0)
        {
            ret_val1 = 0;
        }

        if (check != 0)
        {
            close(out);
            dup2(stdoutCopy, 1);
            close(stdoutCopy);
        }
        close(pip[0]);
        dup2(stdincpy, 0);
        close(stdincpy);
        /////////////////////////////////////////////////////////////
    }
    else
    {
        for (int k = 0; k < j; k++)
        {
            pipeBef[k] = (char *)malloc(sizeof(char) * 100);
            strcpy(pipeBef[k], words[k]);
        }
        pipeBef[j] = NULL;
        int stdoutCopy;
        int stdinCopy;
        stdoutCopy = dup(1);
        stdinCopy = dup(0);
        pipe(pip);
        dup2(pip[1], 1);
        ////////////////////////////////////////////////////////////////////////////
        int in;
        char filen2[1024];
        int check = 0;
        int c = 0;

        if (pipeBef[0] != NULL)
        {
            if (strcmp(pipeBef[0], "cd") == 0 || strcmp(pipeBef[0], "echo") == 0 || strcmp(pipeBef[0], "pwd") == 0 || strcmp(pipeBef[0], "ls") == 0 || strcmp(pipeBef[0], "history") == 0 || strcmp(pipeBef[0], "discover") == 0 || strcmp(pipeBef[0], "pinfo") == 0)
            {
                for (int i = 0; i < index_pipe; i++)
                {
                    if (strcmp(pipeBef[i], "<") == 0)
                    {
                        strcpy(filen2, pipeBef[i + 1]);
                        in = open(pipeBef[i + 1], O_RDONLY);
                        for (int j = i; j < i + 2 && j < index_pipe; j++)
                        {
                            pipeBef[j] = pipeBef[j + 2];
                        }
                        pipeBef[noOfArgs - 1] = NULL;
                        pipeBef[noOfArgs - 2] = NULL;
                        noOfArgs = noOfArgs - 2;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < index_pipe; i++)
                {
                    if (strcmp(pipeBef[i], "<") == 0)
                    {
                        c = 1;
                        for (int j = i; j < index_pipe; j++)
                        {
                            pipeBef[i] = pipeBef[i + 1];
                        }
                        pipeBef[index_pipe - 1] = NULL;
                        noOfArgs--;

                        break;
                    }
                }
            }
        }
        int stdoutCopy1;
        if (check != 0)
        {
            stdoutCopy1 = dup(1);
            dup2(pip[1], 1);
        }

        int ret_val = exec(pipeBef, prev_path, prev_path1, root, index_pipe, fptr, ListOfHistory, d, i, flag, tag_b, back, back_final);
        if (ret_val == 0)
        {
            ret_val1 = 0;
        }

        if (check != 0)
        {
            close(pip[1]);
            dup2(stdoutCopy1, 1);
            close(stdoutCopy1);
        }

        ////////////////////////////////////////////////////////////////////////////
        dup2(stdoutCopy, 1);
        close(pip[1]);
        close(stdoutCopy);
        dup2(pip[0], 0);
        char *new_words[100];
        for (int k = 0; k < 100; k++)
        {
            new_words[k] = (char *)malloc(sizeof(char) * 1000);
        }

        int n = 0;
        if (c == 0)
        {
            for (int j = index_pipe + 1; j < noOfArgs; j++)
            {
                strcpy(new_words[j - index_pipe - 1], words[j]);
                n++;
            }
        }
        if (c == 1)
        {
            for (int j = index_pipe + 1; j <= noOfArgs; j++)
            {
                strcpy(new_words[j - index_pipe - 1], words[j]);
                n++;
            }
        }
        new_words[j - index_pipe + n] = NULL;
        noOfArgs = noOfArgs - j - 1;
        exec_pipe(pipeBef, new_words, prev_path, prev_path1, root, noOfArgs, fptr, ListOfHistory, d, i, flag, tag_b, back, back_final);
        dup2(stdinCopy, 0);
        close(pip[0]);
    }
    return ret_val1;
}

int exec(char *words[], char prev_path[], char prev_path1[], char root[], int noOfArgs, FILE *fptr, char *ListOfHistory[], int d, int i, int flag, int tag_b, struct bg *back, struct bg_final back_final[])
{
    int ret_val = 1;
    if (words[0] != NULL)
    {
        if (strcmp(words[0], "cd") == 0)
        {
            exec_cd(words, prev_path1, prev_path, root, noOfArgs);
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
            ret_val = 0;
        }
        else if (strcmp(words[0], "discover") == 0)
        {
            exec_discover(root, words, noOfArgs);
        }
        else if (strcmp(words[0], "pinfo") == 0)
        {
            func_pinfo(root, words[1], i - 1);
        }
        else if (strcmp(words[0], "jobs") == 0)
        {
            int tag = 0;
            for (int i = 0; i < noOfArgs; i++)
            {
                if (strcmp(words[i], "-s") == 0)
                {
                    tag = 1;
                }
                else if (strcmp(words[i], "-r") == 0)
                {
                    tag = 2;
                }
            }
            jobs_func(back_final, tag);
        }
        else if (strcmp(words[0], "sig") == 0)
        {
            sig(back_final, words[1], words[2]);
        }
        else if (strcmp(words[0], "bg") == 0)
        {
            bg(back_final, words[1]);
        }
        else if (strcmp(words[0], "fg") == 0)
        {
            fg(back_final, words[1]);
        }
        else
        {
            if (tag_b == 0)
                foreGround(words);
            else
                backGround(words, back);
        }
    }
    return ret_val;
}
struct bg *back;
char *line;
int shell_pid;

int main()
{
    int out, in;
    back = (struct bg *)malloc(sizeof(struct bg));
    temp_back.total = 0;
    signal(SIGINT, c_handler);
    signal(SIGTSTP, z_handler);
    shell_pid = getpid();
    char *token;
    char *words[512];
    int noOfArgs;
    int tag_b;
    char command1[1024];
    char *pipeBef[100];
    char *pipeAft[100];

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
    struct bg_final back_final[100];
    gethostname(hostname, 100);
    char prev_path[1024] = "a";
    char prev_path1[1024];
    clearScreen();
    while (1)
    {
        int i, j;
        display(root, hostname);
        diff = 0;
        line = NULL;
        size_t buffersize = 0;
        int ret = getline(&line, &buffersize, stdin);
        if (ret == -1)
        {
            printf("\n");
            return 0;
        }

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
                int index_pipe = -1;
                noOfArgs = z - 1;
                for (j = 0; j < noOfArgs; j++)
                {
                    if (strcmp(words[j], "|") == 0)
                    {
                        index_pipe = j;
                        break;
                    }
                }
                int count = 0;
                for (int i = 0; i < index_pipe; i++)
                {
                    if (strcmp(words[i], "<") == 0 || strcmp(words[i], ">") == 0 || strcmp(words[i], ">>") == 0)
                    {
                        count++;
                    }
                }
                if (count == 2)
                {
                    index_pipe = -1;
                }

                if (index_pipe == -1)
                {
                    char filen[1024];
                    char filen2[1024];
                    noOfArgs = z - 1;
                    int check = 0;
                    for (int i = 0; i < noOfArgs; i++)
                    {
                        if (strcmp(words[i], ">") == 0)
                        {
                            strcpy(filen, words[i + 1]);
                            out = open(words[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
                            check = 1;
                            for (int j = i; j < noOfArgs; j++)
                            {
                                words[j] = NULL;
                            }
                            noOfArgs = i;
                            break;
                        }
                        else if (strcmp(words[i], ">>") == 0)
                        {
                            strcpy(filen, words[i + 1]);
                            out = open(words[i + 1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                            check = 1;
                            for (int j = i; j < noOfArgs; j++)
                            {
                                words[j] = NULL;
                            }
                            noOfArgs = i;
                            break;
                        }
                    }
                    if (words[0] != NULL)
                    {
                        if (strcmp(words[0], "cd") == 0 || strcmp(words[0], "echo") == 0 || strcmp(words[0], "pwd") == 0 || strcmp(words[0], "ls") == 0 || strcmp(words[0], "history") == 0 || strcmp(words[0], "discover") == 0 || strcmp(words[0], "pinfo") == 0)
                        {
                            for (int i = 0; i < noOfArgs; i++)
                            {
                                if (strcmp(words[i], "<") == 0)
                                {
                                    strcpy(filen2, words[i + 1]);
                                    in = open(words[i + 1], O_RDONLY);
                                    for (int j = i; j < i + 2 && j < noOfArgs; j++)
                                    {
                                        words[j] = words[j + 2];
                                    }
                                    words[noOfArgs - 1] = NULL;
                                    words[noOfArgs - 2] = NULL;
                                    noOfArgs = noOfArgs - 2;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < noOfArgs; i++)
                            {
                                if (strcmp(words[i], "<") == 0)
                                {
                                    for (int j = i; j < noOfArgs - 1; j++)
                                    {
                                        words[i] = words[i + 1];
                                    }
                                    words[noOfArgs - 1] = NULL;
                                    noOfArgs--;
                                    break;
                                }
                            }
                        }
                    }
                    int stdoutCopy;
                    if (check != 0)
                    {
                        stdoutCopy = dup(1);
                        dup2(out, 1);
                    }

                    int ret_val = exec(words, prev_path, prev_path1, root, noOfArgs, fptr, ListOfHistory, d, i, flag, tag_b, back, back_final);
                    if (ret_val == 0)
                    {
                        return 0;
                    }

                    if (check != 0)
                    {
                        close(out);
                        dup2(stdoutCopy, 1);
                        close(stdoutCopy);
                    }
                }
                else
                {
                    int ret_val = exec_pipe(pipeBef, words, prev_path, prev_path1, root, noOfArgs, fptr, ListOfHistory, d, i, flag, tag_b, back, back_final);
                    if (ret_val == 0)
                    {
                        return 0;
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