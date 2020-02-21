#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


int main(){
	char ch1[10], ch2[5] = "bbbbb";
	int fd, p;

	fd=open("data", O_RDWR);
	read(fd, ch1, 5);
	write(1, ch1, 5);

	write(fd, ch2, 5);
	read(fd, ch1, 5);
	write(1, ch1, 5);

	p=lseek(fd, -10, SEEK_CUR);
	printf("%d\n", p);

	read(fd, ch1, 10);
	write(1, ch1, 10);

	return 0;
}

