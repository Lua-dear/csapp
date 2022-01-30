#include "shell.h"
int builtin_command(char **argv)
{
	proc jobs=list;
	char *word;
	if(!strcmp(argv[0],"jobs"))//
	{
		if(jobs->next==NULL)
			return 1;
		while(jobs->next!=NULL)
		{
			if(jobs->next->jid!=0)
			{
				if(jobs->next->state==1||jobs->next->state==2)
					printf("[%d] %d %s %s\n",jobs->next->jid,jobs->next->pid,"Running",jobs->next->cmd);
				else if(jobs->next->state==3)
					printf("[%d] %d %s %s\n",jobs->next->jid,jobs->next->pid,"Stopped",jobs->next->cmd);
			}
			jobs=jobs->next;	
		}
		return 1;
	}
	if(!strcmp(argv[0],"fg")||!strcmp(argv[0],"bg"))
	{
		if(argv[1]!=NULL)
		{
			proc job=serjob(argv[1]);
			if(job==NULL)
			{
				printf("%d:No such job!\n",atoi(argv[1]));
				return 1;	
			}
			fgbg(job,argv[0]);
		}
		else
			printf("%s: current: no such job\n",argv[0]);
		return 1;	
	}
	if(!strcmp(argv[0],"quit"))
		exit(0);
	return 0;
}
