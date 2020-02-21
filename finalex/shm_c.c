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

struct databuf{
	int flag;
	int data;
};

int main(){
	int shmid, i;
	key_t key;
	struct databuf *buf;

	key = ftok("key", 22);
	shmid = shmget(key, N*sizeof(struct databuf), 0600|IPC_CREAT|IPC_EXCL);
	buf = (struct databuf *)shmat(shmid, 0, 0);



	exit(0);
}
