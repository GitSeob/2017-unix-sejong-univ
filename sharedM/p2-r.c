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

struct buf_data{
	int flag;
	int data;
};

int main(){
	int shmid, i;
	key_t key;
	struct buf_data *databuf;

	key = ftok("shmkey", 3);
	shmid = shmget(key, 10*sizeof(struct buf_data), 0600|IPC_CREAT);
	databuf = (struct buf_data *)shmat(shmid, 0, 0);

	for(i=0;i<10;i++){
		while((databuf+i)->flag==0);
		printf("%d\n", (databuf+i)->data);
	}

	shmctl(shmid, IPC_RMID, 0);

	exit(0);
}
