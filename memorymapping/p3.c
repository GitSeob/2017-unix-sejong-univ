#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	int i, fd, len=0;
	char *addr;

	fd = open("temp", O_RDWR|O_CREAT, 0600);

	addr = mmap(NULL, 3*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	ftruncate(fd, 512);

	for(i=0;i<3;i++){
		len = len+read(0, addr+len, 512);
		if(len>512)
			break;
	}

	exit(0);
}
