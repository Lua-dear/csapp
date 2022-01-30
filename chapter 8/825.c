#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<setjmp.h>
sigjmp_buf buf;
void handler(int sig)
{
	siglongjmp(buf,1);
}
char* tfgets(char*s,int size,FILE*stream)
{
	if(!sigsetjmp(buf,1))
	{
		alarm(5);
		signal(SIGALRM,handler);
		return fgets(s,size,stream);
	}
	else
		return NULL;
}
int main()
{
	char buf[100];
	char *input=tfgets(buf,100,stdin);
	if(input==NULL)
	{
		printf("time out!\n");
	}
	else
		printf("%s",input);
	return 0;
}
