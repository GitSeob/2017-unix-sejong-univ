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
#include <sys/mman.h>
#include <sys/shm.h>

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(){
	int shmid, i, in, semid, *buf;
	union semun arg;
	struct sembuf p_buf;
	key_t key1, key2;
	
	key1 = ftok("shmkey", 1);
	semid = semget(key1, 1, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1){
		semid=semget(key1, 1, 0600);
	}
	else{
		arg.val = 0;
		semctl(semid, 0, SETVAL, arg);
	}

	key2 = ftok("shmkey", 2);
	shmid = shmget(key2, 10*sizeof(int), 0600|IPC_CREAT);
	buf = (int *)shmat(shmid, 0, 0);

	for(i=0;i<10;i++){
		scanf("%d", (buf+i));
		p_buf.sem_num = 0;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}


	exit(0);
}
