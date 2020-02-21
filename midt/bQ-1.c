#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv){
	int sum,fd1, fd2, i;
	int inputnum[10];

	sum = 0;

	fd1 = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600);
	fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
 

	for(i=0;i<10;i++){
		scanf("%d", &inputnum[i]);
		write(fd1, &inputnum[i], sizeof(int));
		sum += inputnum[i];
		raise(SIGUSR1);
	}

	write(fd2, &sum, sizeof(int));

	exit(0);
}
