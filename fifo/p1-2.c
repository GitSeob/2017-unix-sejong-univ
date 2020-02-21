#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd1, fd2, i, n, input, sum;

	if((fd1=open("fifo1", O_WRONLY|O_NONBLOCK))<0){
		printf("fail\n");
		exit(1);
	}

	fd2 = open("fifo2", O_RDONLY);

	while(1){
		//n = read(0, &input, sizeof(int));
		scanf("%d", &input);
		write(fd1, &input, sizeof(int));
		if(input == -1){
			printf("i got a -1 value\n");
			exit(0);
		}
		read(fd2, &sum, sizeof(int));
		//write(1, &sum, sizeof(int));
		printf("%d\n", sum);
	}

	exit(0);
}
