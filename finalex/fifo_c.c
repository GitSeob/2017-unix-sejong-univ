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

int main(){
	int fd1, fd2, n, in, sum;

	if((fd1 = open("fifo1", O_WRONLY|O_NONBLOCK))<0){
		exit(1);
	}

	fd2 = open("fifo2", O_RDONLY);

	for(;;){
		scanf("%d", &in);
		write(fd1, &in, sizeof(int));
		if(in == -1){
			exit(0);
		}
		read(fd2, &sum, sizeof(int));
		printf("%d\n", sum);
	}


	exit(0);
}
