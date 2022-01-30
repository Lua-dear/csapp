#include "shell.h"
void command(char *cmd)
{
	char **argv;
	proc job;
	job=init_job(job);
	susflag=0;
	arg=(char*)malloc(sizeof(char)*MAX);
	strcpy(arg,cmd);
	if((argv=detach(arg,argv))==NULL)
		return;
	sigset_t mask,prev_one,mask_one,prev;
	sigemptyset(&mask);
	sigemptyset(&prev);
	sigemptyset(&prev_one);
	sigemptyset(&mask_one);
	sigfillset(&mask);
	sigaddset(&mask_one,SIGCHLD);
	signal(SIGCHLD,sigchild_handler);
	signal(SIGINT,sigint_handler);
	signal(SIGTSTP,sigstop_handler);
	if(argv[0]==NULL)
		return ;
	if(!builtin_command(argv))
	{
		sigprocmask(SIG_BLOCK,&mask_one,&prev_one);
		if((pid=fork())==0)
		{
			sigprocmask(SIG_SETMASK,&prev_one,NULL);
			if(setpgid(0,0)<0)
			{
				fprintf(stderr,"Error set pid!!!");
				exit(0);
			}
			if(execve(argv[0],argv,environ)<0)
			{
				printf("%s:command not found!!!\n",argv[0]);
				exit(0);
			}	
		}
		sigprocmask(SIG_BLOCK,&mask,&prev);
		addjob(job);
		sigprocmask(SIG_SETMASK,&prev,NULL);
		if(bfg)
		{
			addjid(job->pid);
			printf("[%d] %d %s\n",job->jid,job->pid,arg);
		}
		else
		{
			
			while(!susflag)
				sigsuspend(&prev_one);	
		}
		sigprocmask(SIG_SETMASK,&prev_one,NULL);
	}
	return;
}
