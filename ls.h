#ifndef __LS_H
#define __LS_H

static int myCompare(const void *a, const void *b);
void bubbleSort(const char *arr[], int n);
void ls_l_func(char filename[]);
void ls_func(char *path, int a);
void ls_l(char *path, int a);
void exec_ls(char * root,char * words[],int noOfArgs);
void printTotal(DIR *d, struct dirent *dir, char path[],int a);

#endif