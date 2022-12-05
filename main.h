#include"headers.h"
#ifndef __MAIN_H
#define __MAIN_H

int exec(char *words[], char prev_path[], char prev_path1[], char root[], int noOfArgs, FILE *fptr, char *ListOfHistory[], int d, int i, int flag, int tag_b, struct bg *back,struct bg_final back_final[]);
int exec_pipe(char *pipeBef[], char *words[], char prev_path[], char prev_path1[], char root[], int noOfArgs, FILE *fptr, char *ListOfHistory[], int d, int i, int flag, int tag_b, struct bg* back,struct bg_final back_final[]);
#endif