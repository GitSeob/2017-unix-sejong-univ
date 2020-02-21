#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
	char buf[2];
	int i, fd;

	fd = open("data", O_RDONLY);
	for(i=0; i<10; i++){
		read(fd, buf, 1);
		write(1, buf, 1);
		write(1, "\n", 1);
		sleep(1);
	}

	exit(atoi(argv[1]));
}
