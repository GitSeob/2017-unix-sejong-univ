#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <signal.h>

#define N 3

int main(){
	int fd1, fd2, sum, n, in;

	mkfifo("fifo1", 0600);
	mkfifo("fifo2", 0600);

	fd1 = open("fifo1", O_RDONLY);
	fd2 = open("fifo2", O_WRONLY);

	for(;;){
		n = read(fd1, &in, sizeof(int));
		printf("%d\n", &in);
		if(in == -1){
			exit(0);
		}
		sum = in+8;
		write(fd2, &sum, sizeof(int));
	}

	exit(0);
}
