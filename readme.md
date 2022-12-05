# Assignment2
## Name:Vanshika Dhingra
## Roll-NO: 2021101092
---
---
### files present and their description

> makefile 
* on typing make an executable file a.out is created
---
> .h files contain prototypes for functions in .c files
* while the headers.h contains all the #include statements

---
> main.c
* 

> cd.c   
* changes the directory
* on typing cd - on first command gives error that old path is not set
* while on subsequent commands it changes directory to previous directory and prints its path
* if no of arguments to cd is greater than one then it gives error:Too many arguments
* on passing an file name or an invalid folder name to cd it gives error this has been handled using perror
---
> echo.c
* what ever is written as an argument of echo gets printed on the terminal
---
> pwd.c
* gives the path of current directory
---
> ls .c
*   handles multiple tags and files in any order
*   files are coloured red 
*   folders are coloured green
 ---
> display.c
* prints the intial prompt
* when a foreground process is called if ita running time is greater than or equal to 1 sec then the time taken by it is printed
* when a background process exits the process name,its pid and its exiting status is printed
---
> history.c
* the latest 10 commands that were executed are printed using this command and it has a buffer of 20 commands after which it starts overwriting the previous commands
* upon exiting the commands are written to the file named history.txt so that it is preserved over all sessions.
* if the command matches with the previous commands it is not written to history again
---
> discover.c
* if we enter a folder or a file that does not exist it gives error
* multiple -d and -f tags are handled
---
> pinfo.c
* prints the pid
* status
* memory
* execuatable path
---
> syscommands.c
* in both foreground and background processes first a fork system call is made
* then an execvp system call is made for he child process i.e. when the fork return is 0
* now for the foreground process waitpid is called for the parent process while for the background process the pid and commands names are stored in a struct.
---
> signalHandlers.c
* functions for handling ctrl+c and ctrl+z are provided
* whenever the program gets the signal SIGINT and SIGTSTP these routines are triggered

___

> jobs.c
* has functions for jobs,sig,fg,bg
* jobs prints all the jobs in alphabetical order
* jobs -s prints all the stopped jobs in alphabetical order
* jobs -r prints all the running jobs in alphabetical order
* sig bg and fg work on an id and if the process with id a does not exist it throws an error