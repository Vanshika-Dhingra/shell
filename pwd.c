#include"headers.h"

char* pwd_func()
{
	int size = 1000;
	char *pwd = (char *)malloc(size*sizeof(char));
	getcwd(pwd,1024);
	printf("%s\n",pwd);
	return pwd;
}


