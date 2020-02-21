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


int main(int argn, char **argv){
	int shmid, i, *buf, id, pid;
	key_t key;
	
	id = atoi(argv[1]);
	pid = getpid();

	key = ftok("shmkey", 4);
	shmid = shmget(key, 4*sizeof(int), 0600|IPC_CREAT);
	buf = (int *)shmat(shmid, 0, 0);

	if(id>1){
		while(*(buf) != id);
	}
	for(i=0;i<5;i++){
		sleep(1);
		printf("I'm %d ....... %d\n", pid, id);
	}

	if(id<4){
		*buf = id+1;
	}
	else if(id == 4){
		shmctl(shmid, IPC_RMID, 0);
	}

	exit(0);
}
