#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<setjmp.h>
#include<stdlib.h>
#define N 2
int *test=(int*)0x40000008;
extern int errno;
char buf[100];
void handler(int sig)
{
	sprintf(buf,"child %d terminated by signal %d",getpid(),WTERMSIG(sig));
	psignal(WTERMSIG(sig),buf);
	exit(sig);	
}
int main()
{
	int i,status;
	pid_t pid;
	signal(SIGSEGV,handler);
	for(i=0;i<N;i++)
	{
		if((pid=fork())==0)
		{
			*test=8;
		}
	}
	while((pid=waitpid(-1,&status,0))>0)
	{
		if(WIFSIGNALED(status))
			printf("child %d terminated normally with exit status=%d\n",pid,WEXITSTATUS(status));
		if(!WIFEXITED(status))
			printf("child %d terminated abnormally\n",pid);
	}
	if(errno!=ECHILD)
	{
		printf("waitpid error\n");
	}
	exit(0);
}
