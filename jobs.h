#ifndef __JOBS_H
#define __JOBS_H

void jobs_func(struct bg_final back_final[],int tag);
void sig(struct bg_final back_final[],char a[],char b[]);
void bg(struct bg_final back_final[], char a[]);
void fg(struct bg_final back_final[], char a[]);

#endif