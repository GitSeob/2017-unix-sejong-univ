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

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(){
	int i, semid, id;
	union semun arg;
	struct sembuf p_buf;
	key_t key;

	key = ftok("key", 33);
	semid = semget(key, N, 0600|IPC_CREAT|IPC_EXCL);
	
	if(semid == -1){
		semid = semget(ket, 3, 0600);
	}
	else{
		arg.val = 0;
		//arg.array = buf;
		semctl(semid, 0, SETVAL, arg);
		//SETVAL arg값으로 semval값 지정
		//SETVAL semval값 리턴
		//GETPID sempid값 리턴
		//GETNCNT semncnt값 리턴
		//GETZCNT semzcnt값 리턴
		//GETALL 모든 semval값을 arg.array에 저장
		//SETALL arg.array값으로 모든 semval값 지정
	
	}
	
	p_buf.sem_num = semindex;
	p_buf.sem_op = 1 or -1;
	p_buf.sem_flag = 0; // IPC_NOWAIT일때만 사용
	semop(semid, &p_buf, 1);


	semctl(semid, 0, IPC_RMID, arg);
	exit(0);
}
