#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int nn = 35;
	int i,fd;
	fd = open("test2", O_WRONLY|O_CREAT, 0640);
	for(i=0;i<10;i++){
		write(fd, &nn, sizeof(int));
	}	
	// use pointer of int type..
	printf("done\n");

	return 0;
}
