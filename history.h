#ifndef __HISTOR_H
#define __HISTOR_H

void write_history(FILE * fptr,char  ListOfHistory[][200],int d,int i);
void exit_history(int flag, char *root, FILE *fptr, char ListOfHistory[][200], int d);

#endif