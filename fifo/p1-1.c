#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd1, fd2,  n, sum, inputn;

	mkfifo("fifo1", 0600);
	mkfifo("fifo2", 0600);

	fd1 = open("fifo1", O_RDONLY);
	fd2 = open("fifo2", O_WRONLY);

	for(;;){
		n = read(fd1, &inputn, sizeof(int));
		printf("%d\n", inputn);
		if(inputn == -1){
			printf("i got a -1 value\n");
			exit(0);
		}
		sum = inputn+8;
		printf("%d -> %d\n", inputn, sum);
		write(fd2, &sum, sizeof(int));
	}

}
