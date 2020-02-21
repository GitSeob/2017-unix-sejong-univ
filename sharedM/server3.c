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

int main(){
	int shmid, cal, i, j=0;
	key_t key;
	struct databuf *buf;

	key = ftok("shmkey", 10);
	shmid = shmget(key, 3*sizeof(struct databuf), 0600|IPC_CREAT);
	buf = (struct databuf *)shmat(shmid, 0, 0);

	while(1){
		for(i=0;i<3;i++){
			if((buf+i)->flag == 1){
				cal = (buf+i)->data+8;
				(buf+i)->data = cal;
				(buf+i)->flag = 0;
				j++;
				printf("%d : %d : %d\n", j, cal, (buf+i)->data);
			}
		}
		if(j==15)
			break;
	}

	shmctl(shmid, IPC_RMID, 0);
	
	exit(0);
}
