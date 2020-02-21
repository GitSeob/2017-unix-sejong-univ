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

int main(){
	int i, fd1;
	char f2[6][2] = {"a","b","c","d","e","f"};

	fd1 = open("TEMP", 0666|O_CREAT);

	for(i=0;i<6;i++){
		write(fd1, f2[i], sizeof(char));
	}


	exit(0);
}
