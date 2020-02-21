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

#define N 10

int main(){
	int i, fd, input;
	int *addr_int;
	char *addr_char;

	fd = open("temp", O_RDWR|O_CREAT, 0600);

	addr_char = mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	//void *mmap(*addr(보통 NULL), size, prot(PROT_READ, PROT_WRITE), 
	//	flags(MAP_SHARED), offset);

	ftruncate(fd, N);
	//무조건 해줘야함 필수!!
	
	printf("%s", addr_char);


	exit(0);
}
