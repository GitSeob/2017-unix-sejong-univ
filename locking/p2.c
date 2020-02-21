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
	int i, fd;
	pid_t pid;
	struct flock lock;

	pid = getpid();
	fd = open("turn1", O_RDWR|O_CREAT, 0600);

	lock.l_whence = SEEK_SET;
	lock.l_len = 1;
	lock.l_type = F_WRLCK;
	lock.l_start = 0;

	fcntl(fd, F_SETLKW, &lock);

	for(i=0;i<5;i++){
		sleep(1);
		printf("%d....\n", pid);
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	exit(0);
}
