#include "headers.h"

extern int shell_pid;
extern struct bg temp_back;

int comparator(const void *p, const void *q)
{
    return strcmp(((struct bg_final *)p)->command, ((struct bg_final *)q)->command);
}

void jobs_func(struct bg_final back_final[], int tag)
{
    char file[1024];
    char string[4][1024];
    int count = 0;
    for (int i = 0; i < 100; i++)
    {
        if (temp_back.pid[i] != 0)
        {
            sprintf(file, "/proc/%d/stat", temp_back.pid[i]);

            FILE *fptr = fopen(file, "r");

            if (fptr != NULL)
            {
                fscanf(fptr, "%s", string[0]);
                fscanf(fptr, "%s", string[1]);
                fscanf(fptr, "%s", string[2]);

                char status[1024];
                if (strcmp("T", string[2]) == 0)
                {
                    strcpy(temp_back.status[i], "Stopped");
                }
                else
                {
                    strcpy(temp_back.status[i], "Running");
                }
                // back_final[i] = (struct bg_final *)malloc(sizeof(struct bg_final));
                back_final[count].pid = temp_back.pid[i];
                strcpy(back_final[count].command, temp_back.command[i]);
                back_final[count].id = temp_back.id[i];
                strcpy(back_final[count].status, temp_back.status[i]);
                // printf("[%d] %s %s [%d]\n", back_final[i].id, back_final[i].status, back_final[i].command, back_final[i].pid);
                fclose(fptr);
                count++;
            }
        }
        else
        {
            continue;
        }
    }

    qsort(back_final, count, sizeof(*back_final), comparator);
    if (tag == 0)
    {
        for (int i = 0; i < count; i++)
        {
            printf("[%d] %s %s [%d]\n", back_final[i].id, back_final[i].status, back_final[i].command, back_final[i].pid);
        }
    }
    else if (tag == 1)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(back_final[i].status, "Stopped") == 0)
                printf("[%d] %s %s [%d]\n", back_final[i].id, back_final[i].status, back_final[i].command, back_final[i].pid);
        }
    }
    else if (tag == 2)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(back_final[i].status, "Running") == 0)
                printf("[%d] %s %s [%d]\n", back_final[i].id, back_final[i].status, back_final[i].command, back_final[i].pid);
        }
    }
}

void sig(struct bg_final back_final[], char a[], char b[])
{
    int int_a = atoi(a);
    int int_b = atoi(b);
    char file[1024];
    sprintf(file, "/proc/%d/stat", temp_back.pid[int_a - 1]);

    FILE *fptr = fopen(file, "r");

    if (fptr != NULL)
    {
        kill(temp_back.pid[int_a - 1], int_b);
    }
    else
    {
        perror("error");
    }
}

void bg(struct bg_final back_final[], char a[])
{
    int int_a = atoi(a);
    char file[1024];
    sprintf(file, "/proc/%d/stat", temp_back.pid[int_a - 1]);

    FILE *fptr = fopen(file, "r");

    if (fptr != NULL)
    {
        kill(temp_back.pid[int_a - 1], SIGCONT);
    }
    else
    {
        perror("error");
    }
}

void fg(struct bg_final back_final[], char a[])
{
    int int_a = atoi(a);
    char file[1024];
    sprintf(file, "/proc/%d/stat", temp_back.pid[int_a - 1]);

    FILE *fptr = fopen(file, "r");
char fileName[1024];
  char status;
  int retValue = 0;

  for (int i = 1; i < 100; i++) {
    if (!bgPid[i]) continue;

    sprintf(fileName, "/proc/%d/stat", bgPid[i]);

    FILE* file = fopen(fileName, "r");

    if (file) {
      fscanf(file, "%*d %*s %c", &status);

      printf("[%d] %s %s [%d]\n", i, status == 'T' ? "Stopped" : "Running",
             bgCommand[i], bgPid[i]);

    } else {
      perror("Error");
      retValue = -1;
    }

    fclose(file);
  }

  return retValue;
    if (fptr != NULL)
    {
        int status;
        int int_a = atoi(a);
        pid_t pid = temp_back.pid[int_a - 1];
        setpgid(pid, getpgid(0));

        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        tcsetpgrp(0, pid);

        kill(pid, SIGCONT);

        waitpid(pid, &status, WUNTRACED);

        tcsetpgrp(0, getpgid(0));

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        if (WIFSTOPPED(status))
            return 0;
        if (!pid)
            return;

        for (int i = 1; i < 100; i++)
        {
            if (temp_back.pid[i] == pid)
            {
                temp_back.pid[i] = 0;
                free(temp_back.command[i]);
                break;
            }
        }
        return WIFEXITED(status) ? pid : -pid;
    }
    else
    {
        perror("error");
    }
}
