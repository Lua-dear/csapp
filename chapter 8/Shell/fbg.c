#include "shell.h"
void fgbg(proc job,char *fg)
{
	sigset_t mask,prev;
	sigemptyset(&mask);
	sigemptyset(&prev);
	sigaddset(&mask,SIGCHLD);
	if(!strcmp(fg,"fg"))
	{
		if(job->state==BG)
		{
			job->state=FG;
			sigprocmask(SIG_BLOCK,&mask,&prev);
			deljid(pid);
			printf("job jid:%d\n",job->jid);
			while(!susflag)
				sigsuspend(&prev);	
			sigprocmask(SIG_SETMASK,&prev,NULL);
	
		}
		else if(job->state==ST)
		{
			job->state=FG;
			kill(-(job->gpid),SIGCONT);
			sigprocmask(SIG_BLOCK,&mask,&prev);
			while(!susflag)
				sigsuspend(&prev);	
			sigprocmask(SIG_SETMASK,&prev,NULL);
		}
		else
			printf("fg error!\n");
	}
	else
	{
		if(job->state==ST)
		{
			job->state=BG;
			kill(-(job->gpid),SIGCONT);
			printf("[%d] %d %s\n",job->jid,job->pid,job->cmd);
		}
		if(job->state==FG||job->state==undef)
			printf("bg error!!!\n");
	}
}
