#include "headers.h"

extern struct bg *back;
extern struct bg temp_back;
extern char *line;
extern ret_fork;

void c_handler()
{
    int pid=ret_fork;
    kill(pid,signal);
}

void z_handler()
{
    int pid=getpid();
    temp_back.pid[temp_back.total]=ret_fork;
    strcpy(temp_back.command[temp_back.total],line);

}
