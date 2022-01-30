#include "shell.h"
int main()
{
	char cmd[MAX];
	init_proc();
	init_jid();
	while(1)
	{

		printf("LuaShell>>");
		fgets(cmd,MAX,stdin);
		if(feof(stdin))
			exit(0);
		command(cmd);
		//fflush(stdin);
		//fflush(stdout);
	}
	exit(0);
}
