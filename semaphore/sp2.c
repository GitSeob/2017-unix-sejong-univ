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

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main(){
	int i, fd, semid, m, len=0;
	char *addr, *outchar;
	union semun arg;
	struct sembuf p_buf;
	key_t key;

	key = ftok("semkey", 1);

	semid = semget(key, 1, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1)
		semid = semget(key, 1, 0600);
	else{
		arg.val = 0;
		semctl(semid, 0, SETVAL, arg);
	}

	fd = open("temp", O_RDWR|O_CREAT, 0600);
	addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	ftruncate(fd, 512);

	for(i=0;i<3;i++){
		p_buf.sem_num = 0;
		p_buf.sem_op = -1;
		p_buf.sem_flg = 0;
		semop(semid, &p_buf, 1);
		write(1, addr+len, 50);
		len = len + strlen(addr+len)+1;
	}

	exit(0);
}
