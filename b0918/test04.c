#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int argnum, i;
	pid_t forkid;
	int fd;
	char readChar[2];

	if(argc = 3){
		fd = open(argv[1], O_RDONLY);
		argnum = atoi(argv[2]);
		//printf("%d\n", argnum);
		//forkid = fork();
		i =0;
		while(i<argnum){
			forkid = fork();
			if(forkid!=0){
				printf("create %d Child Process!\n",i+1);
				wait((int*)0);
				//forkid = fork();
			}
			else{
				//printf("Child Process ID : %ld | Group ID : %ld | Session ID : %ld\n", getpid(), getpgrp(), getsid(getpid()));
				read(fd, readChar, sizeof(char)*2);
				printf("%ld PROCESS read data : %s\n", getpid(), readChar);
				//break;
				exit(0);
			}
			i++;
		}
	}
	else{
		printf("error : 인수가 3개가 아닙니다.\n");
	}

	return 0;
}