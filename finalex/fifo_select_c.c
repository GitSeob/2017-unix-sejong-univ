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

int main(int argc, char **argv){
	char f[N*2][3] = {"f1", "f2", "f3", "f4", "f5", "f6"};
	int i, j, k, in, fd[2];

	k = atoi(argv[1]);

	fd[1] = open(f[k], O_WRONLY);
	fd[0] = open(f[k+N], O_RDONLY);

	for(i=0;i<5;i++){
		scanf("%d", &in);
		write(fd[1], &in, sizeof(int));
		read(fd[0], &in, sizeof(int));
		printf("%d\n", in);
	}

	exit(0);
}
