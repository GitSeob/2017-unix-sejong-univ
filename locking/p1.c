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

void do_child(int fd){
	int num;
	struct flock lock;
	
	lock.l_whence=SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 4;
	lock.l_type = F_WRLCK;

	fcntl(fd, F_SETLKW, &lock);

	lseek(fd, 0, SEEK_SET);
	read(fd, &num, sizeof(int));
	printf("read num in file ....\n");
	sleep(5);

	num = num+10;
	
	lseek(fd, 0, SEEK_SET);
	write(fd, &num, sizeof(int));
	printf("write num of mine in file ....\n");
	sleep(1);

	lock.l_type = F_UNLCK;

	fcntl(fd, F_SETLK, &lock);

	exit(0);
}

int main(){
	int fd, i, num;
	pid_t pid;

	fd = open("data", O_RDWR|O_CREAT, 0600);

	scanf("%d", &num);
	write(fd, &num, sizeof(int));

	for(i=0;i<3;i++){
		pid = fork();
		if(pid == 0)
			do_child(fd);
	}

	for(i=0;i<3;i++){
		wait(0);
	}

	lseek(fd, 0, SEEK_SET);
	read(fd, &num, sizeof(int));
	printf("%d\n", num);

	exit(0);
}
