#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void do_child(int id, int *addr){
	int i, pid;

	if(id<2){
		while(id!=*addr);
	}

	pid = getpid();

	for(i=0;i<5;i++){
		sleep(1);
		printf("%d is %d.......\n", id, pid);
	}

	if(id>0)
		*addr = id-1;


	exit(0);
}

int main(){
	int i, fd, *addr;

	fd = open("temp3", O_RDWR|O_CREAT, 0600);

	addr = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	ftruncate(fd, sizeof(int));

	*addr = 2;

	for(i=0;i<3;i++){
		if(fork()==0){
			do_child(i, addr);
		}
	}

	for(i=0;i<3;i++){
		wait(0);
	}


}
