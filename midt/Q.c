#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int fd1;

void print(){
	int fd1, n;
	read(fd1, &n, sizeof(int));
	printf("%d\n",n);
	//return 0;
}

int main(int argc, char **argv){
	int fd1, fd2, i, n, sum;
	int pid, mpid;
	int status;
	static struct sigaction act;

	pid = fork();
	if(pid==0){
		execl("./a.out", "a.out", argv[1], argv[2], (char *)0);
	}
		
	fd1 = open(argv[1], O_RDONLY);
	
	act.sa_handler = print;
	sigaction(SIGUSR1, &act, NULL);	

	for(i=0;i<10;i++){
		wait(&status);
	}

	wait(&status);

	fd2 = open(argv[2], O_RDONLY);
	read(fd2, &sum, sizeof(int));
	printf("%d\n", sum);

	return 0;

}
