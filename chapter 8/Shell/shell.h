#ifndef SHELL_H
#define SHELL_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
#include<errno.h>
#include<ctype.h>
#define MAX 128
#define undef 0
#define FG 1
#define BG 2
#define ST 3
typedef struct Proc *proc;
struct Proc
{
	pid_t pid;
	pid_t jid;
	pid_t gpid;
	int state;
	char *cmd;
	proc next;
};
extern int errno;
extern char** environ;
proc list;
char *arg;
pid_t jid[MAX];
volatile sig_atomic_t pid;
int bfg;
volatile sig_atomic_t susflag;
void init_proc();
proc init_job(proc job);
void addjob(proc jobs);
void deljob(pid_t pid);
void init_jid();
void addjid(pid_t pid);
void deljid(pid_t pid);
proc serjob(char *ID);
void changestate(pid_t PID,int STATE);
pid_t searjid(pid_t pid);
void fgbg(proc job,char *fg);
char **detach(char *comm,char **argv);
void command(char *cmd);
int builtin_command(char **argv);
void sigchild_handler(int sig);
void sigint_handler(int sig);
void sigstop_handler(int sig);
void sigcont_handler(int sig);
#endif
