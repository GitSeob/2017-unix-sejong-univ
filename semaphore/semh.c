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

int main(){
	int semid, m;
	union semun arg;
	struct sembuf p_buf;



	exit(0);
}
