#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){
	int fd1, fd2, i, n, sum;
	int pid;
	int status;

	pid = fork();
	if(pid==0){
		execl("./a.out", "a.out", argv[1], argv[2], (char *)0);
	}
	
	wait(&status);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	for(i=0;i<10;i++){
		read(fd1, &n, sizeof(int));
		printf("%d\n", n);
	}
	read(fd2, &sum, sizeof(int));
	printf("%d\n", sum);

	return 0;

}
