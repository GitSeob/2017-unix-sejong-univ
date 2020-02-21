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

#define N 1

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(int argn, char **argv){
	int len, id, shmid, semid, i;
	key_t semkey, shmkey;
	struct sembuf p_buf;
	union semun arg;
	char *buf;

	semkey = ftok("key", 55);
	semid = semget(semkey, 1, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1){
		semid = semget(semkey, 1, 0600);
	}
	else{
		arg.val = 0;
		semctl(semid, 0, SETVAL, arg);
	}

	shmkey = ftok("key", 22);
	shmid = shmget(shmkey, 512, 0600|IPC_CREAT);
	buf = (char *)shmat(shmid, 0, 0);
	//할당받은 메모리를 program에 부착
	//shmdt(memptr) : 공간에서만 때어내기
	
	while(1){
		p_buf.sem_num = 0;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		printf("%s\n", buf);
		//buf.data = in;
		if(strcmp(buf, "quit") == 0) break;
	}

	semctl(semid, IPC_RMID, 0);
	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}
