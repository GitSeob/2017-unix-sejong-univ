#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	int i, fd, *addr, input;

	fd = open("temp", O_RDWR|O_CREAT, 0600);

	addr = mmap(NULL, 10*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	ftruncate(fd, sizeof(int)*10);

	for(i=0;i<10;i++){
		scanf("%d", addr+i);
	}

	exit(0);
}
