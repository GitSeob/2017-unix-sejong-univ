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

struct databuf{
	int flag;
	int data;
};

int main(int argn, char **argv){
	int shmid, i, id, in;
	key_t key;
	struct databuf *buf;

	id = atoi(argv[1])-1;

	key = ftok("shmkey", 10);
	shmid = shmget(key, 3*sizeof(struct databuf), 0600|IPC_CREAT);
	buf = (struct databuf *)shmat(shmid, 0, 0);

	for(i=0;i<5;i++){
		scanf("%d", &((buf+id)->data));
		(buf+id)->flag = 1;
		while((buf+id)->flag == 1);
		printf("%d\n", (buf+id)->data);
		}

	exit(0);
}
