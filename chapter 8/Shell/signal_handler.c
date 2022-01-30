#include "shell.h"
void sigchild_handler(int sig)
{
	int old_errno=errno;
	int state;
	sigset_t mask,prev;
	sigemptyset(&mask);
	sigemptyset(&prev);
	sigfillset(&mask);
	while((pid=waitpid(-1,&state,WNOHANG|WUNTRACED))>0)
	{
		sigprocmask(SIG_BLOCK,&mask,&prev);
		susflag=1;
		if(WIFSIGNALED(state))
		{
			printf("Job %d terminated by signal:%d\n",pid,WTERMSIG(state));
			if(bfg)
				deljid(pid);
			deljob(pid);
		}
		if(WIFSTOPPED(state))
		{
			addjid(pid);
			changestate(pid,ST);
			printf("Job [%d] %d stopped by signal:%d\n",searjid(pid),pid,WSTOPSIG(state));
		}
		if(WIFEXITED(state))
		{
			deljid(pid);
			deljob(pid);
		}
		sigprocmask(SIG_SETMASK,&prev,NULL);
	}
	errno=old_errno;
}
void sigint_handler(int sig)
{
	int old_errno=errno;
	int msg,flag=0;
	proc job=list;
	if((msg=kill(-(pid),SIGINT))<0)
		fprintf(stderr,"SIGINT send error: %s\n",strerror(errno));
	errno=old_errno;
	return;
}
void sigstop_handler(int sig)
{
	int old_errno=errno;
	int msg,flag=0;
	proc job=list;
	if(job->next!=NULL)
	{
		if((msg=kill(-(pid),SIGTSTP))<0)
			fprintf(stderr,"SIGTSTP send error: %s\n",strerror(errno));
		errno=old_errno;
	}
	return;
}
