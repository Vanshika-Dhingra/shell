#ifndef __SYS_H
#define __SYS_H

struct bg
{
    int pid[100];
    char  command[100][1000];
    int id[100];
    int total;
    char status[100][1024];
};

struct bg_final
{
    int pid;
    char  command[100];
    int id;
    char status[102];
};

extern long long int diff;
void foreGround(char *words[]);
void backGround(char *words[], struct bg *back);

#endif