#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdarg.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
extern int errno;
extern char** environ;
int mysystem(char *command)
{
	pid_t pid;
	int status;
	if((pid=fork())==0)
	{
	char *arg[4]={"/bin/sh","-c",command,NULL};
	if(execve("/bin/sh",arg,environ)<0)
		fprintf(stderr,"Exec error: %s\n",strerror(errno));	
	}
	if(waitpid(pid,&status,0)>0)
	{
	if(WIFEXITED(status))
		return WEXITSTATUS(status);
	if(WIFSIGNALED(status))
		return WTERMSIG(status);
	}
}
int main(int argc,char**argv)
{
	int err=mysystem(argv[1]);
	printf("code is %d\n",err);
	exit(err);
}
