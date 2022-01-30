#include "shell.h"
int count=0;
int status=0;
void init_proc()
{
	list=(proc)malloc(sizeof(struct Proc));
	list->pid=-1;
	list->jid=0;
	list->gpid=-1;
	list->state=undef;
	list->cmd=NULL;
	list->next=NULL; 
}
proc init_job(proc job)
{
	job=(proc)malloc(sizeof(struct Proc));
	job->state=undef;
	job->jid=0;
	job->pid=-1;
	job->gpid=-1;
	job->cmd=NULL;
	job->next=NULL;
	return job;
}
void addjob(proc jobs)
{
	proc job;
	job=list;
	jobs->pid=pid;
	jobs->gpid=pid;
	jobs->cmd=arg;
	if(bfg==1)
		jobs->state=BG;
	else if(bfg==0)
		jobs->state=FG;
	while(job->next!=NULL)
		job=job->next;
	jobs->next=NULL;
	job->next=jobs;	
}
void deljob(pid_t PID)
{
	proc job=list;
	proc q;
	int flag=0;
	if(job->next==NULL)
	{
		return;
	}
	while(job->next)
	{
		if(job->next->pid==PID)
		{
			flag=1;
			break;
		}
		job=job->next;
	}
	if(flag==0)
	{
		printf("Pid delete error!!!\n");
		return;
	}
	q=job->next;
	job->next=q->next;
}
void init_jid()
{
	for(int i=0;i<MAX;i++)
		jid[i]=0;
}
void addjid(pid_t PID)
{
	status=1;
	proc job=list->next;
	if(job==NULL)
	{
		printf("List is empty!!!\n");
		return;
	}
	while(job)
	{	
		if(job->pid==PID)
		{		
			count++;	
			job->jid=count;
			jid[0]=count;
			jid[count]=PID;
			break;	
		}
		job=job->next;
	}
}
void deljid(pid_t PID)
{
	proc job=list->next;
	int flag=0;
	int num=0;
	if(status==1)
	{	
		for(int i=1;i<=count;i++)
		{
			if(jid[i]==PID)
			{
				jid[i]=0;
				num=1;
				break;
			}	
		}
		while(job&&num==1)
		{
			if(job->pid==PID)
			{
				job->jid=0;
				break;	
			}
			job=job->next;
		}
		for(int i=1;i<=count&&num==1;i++)
			if(jid[i]!=0)
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			count=0;
			jid[0]=0;
		}
			
	}
}
proc serjob(char *ID)
{
	char *id=NULL;
	proc job=list;
	pid_t PID,Jid;
	id=(char *)malloc(sizeof(char)*strlen(ID));
	if((id=strchr(ID,'%')))
	{
		id+=1;
		Jid=atoi(id);
		if(Jid&&(jid[Jid]!=0))
		{
			while(job->next)
			{
				if(job->next->jid==Jid)
				{
					return job->next;
				}
				job=job->next;
			}	
		}	
	}
	if((PID=atoi(ID)))
	{
		if(PID!=0)
			while(job->next)
			{
				if(job->next->pid==PID)
					return job->next;
				job=job->next;
			}
	}
	return NULL;
}
pid_t searjid(pid_t PID)
{
	pid_t Jid;
	for(int i=1;i<=count;i++)
	{
		if(jid[i]==PID)
			Jid=i;
	}
	return Jid;
}
void changestate(pid_t PID,int STATE)
{
	proc job=list;
	while(job->next)
	{
		if(job->next->pid==PID)
		{
			job->next->state=STATE;
			break;
		}
		job=job->next;
	}
}
