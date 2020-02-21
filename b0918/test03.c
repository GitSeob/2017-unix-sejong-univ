#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int argnum, i;
	pid_t forkid;
	if(argc = 2){
		argnum = atoi(argv[1]);
		//printf("%d\n", argnum);
		// forkid = fork();
		i =0;
		while(i<argnum){
			forkid = fork();
			if(forkid!=0){
				printf("create %d Child Process!\n",i+1);
				wait((int*)0);
				// forkid = fork();
			}
			else{
				printf("Child Process ID : %ld | Group ID : %ld | Session ID : %ld\n", getpid(), getpgrp(), getsid(getpid()));
				//break;
				exit(0);
			}
			i++;
		}
	}
	else{
		printf("error : 인수가 2개가 아닙니다.\n");
	}

	return 0;
}