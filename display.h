#ifndef __DISPLAY_H
#define __DISPLAY_H

char *relativePath(char *root, char *cwd);
void clearScreen();
void display(struct bg* back, char *root, char *hostname);

#endif