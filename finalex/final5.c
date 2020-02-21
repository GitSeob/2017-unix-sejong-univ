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

void do_child(int id, int *turn){
	int i;
	pid_t pid;

	while(id!=*turn);
	pid = getpid();
	for(i=0;i<5;i++){
		printf("%d : %ld\n", id, pid);
		sleep(1);
	}
	*turn = id-1;
	exit(0);
}

int main(){
	int fuck, shmid, i;
	int *turn;
	key_t key;
	
	key = ftok("key", 1);
	shmid = shmget(key, sizeof(int), 0600|IPC_CREAT);

	turn = (int *)shmat(shmid, 0, 0);

	*turn = 4;

	for(i=0;i<5;i++){
		if(fork()==0)
			do_child(i, turn);
	}

	for(i=0;i<5;i++)
		wait(0);

	shmctl(shmid, IPC_RMID, 0);


	exit(0);
}
