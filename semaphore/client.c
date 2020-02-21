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

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(int argn, char **argv){
	ushort buf[3] = {0};
	int semid, pid, i, id;
	union semun arg;
	struct sembuf p_buf;
	key_t key;

	id = atoi(argv[1]);
	key = ftok("semkey", 2);

	semid = semget(key, 3, 0600|IPC_CREAT|IPC_EXCL);
	if(semid==-1){
		semid = semget(key, 3, 0600);
	}
	else{
		arg.array=buf;
		semctl(semid, 0, SETALL, arg);
	}

	if(id>1){
		p_buf.sem_num = id-2;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	pid = getpid();
	
	for(i=0;i<5;i++){
		sleep(1);
		printf("I'm ... %d....\n", pid);
	}

	if(id<4){
		p_buf.sem_num = id-1;
		p_buf.sem_op = 1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
	}

	return 0;

}
