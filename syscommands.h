#ifndef __SYS_H
#define __SYS_H

struct bg
{
    int pid[100];
    char  command[100][1000];
};

extern long long int diff;
void foreGround(char *words[]);
void backGround(char *words[],struct bg* back);

#endif