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

int main(){
	char f[N*2][3] = {"f1", "f2", "f3", "f4", "f5", "f6"};
	fd_set set, master;
	int i, j, k, in, fd[N*2];
	struct timeval t;

	for(i=0;i<N;i++){
		fd[i] = open(f[i], O_RDONLY);
		fd[i+N] = open(f[i+N], O_WRONLY);
	}
	
	FD_ZERO(&master);
	for(i=0;i<N;i++)
		FD_SET(fd[i], &master);

	t.tv_sec=20;
	
	while(set = master, select(fd[2]+1, &set, NULL, NULL, &t)>0){
		for(i=0i<N;i++){
			if((j=read(fd[i], &in, sizeof(int)))>0){
				in = in+8;
				write(fd[i+N], &in, sizeof(int));
			}
		}
		t.tv_sec = 20;
	}

	exit(0);
}
