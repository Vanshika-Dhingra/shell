#ifndef __DISCOVER_H
#define __DISCOVER_H

void relpath(char *root, char *path);
void discover(char path[], int i, int j);
void discover_file(char path[], char *filename);
void exec_discover(char * root,char * words[],int noOfArgs);

#endif