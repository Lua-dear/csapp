#include "shell.h"
char** detach(char *comm,char** argv)
{
	char *arg;
        int argc=0;
        argv=(char**)malloc(sizeof(char*)*MAX);
        comm[strlen(comm)-1]=' ';
        while(*comm&&(*comm== ' '))
 	       *comm++;
        while(arg=strchr(comm,' '))
        {
        	argv[argc]=(char*)malloc(sizeof(char)*MAX);
                argv[argc]=comm;
                *arg='\0';
                comm=arg+1;
                argc++;
                while(*comm&&(*comm==' '))
                	comm++;
        }
        argv[argc]=NULL;
        if(argc==0)
        	return NULL;
        if(bfg=(*argv[argc-1]=='&'))
        	argv[argc-1]=NULL;
	return argv;
}

