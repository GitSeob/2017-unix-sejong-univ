#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int fd;

	fd = open("./B/d", O_WRONLY);
	printf("%d\n", fd);
	fd = open("./B", O_WRONLY|O_CREAT, 0666);
	printf("%d\n", fd);
	fd = open("./B/E/k", O_WRONLY|O_CREAT, 0666);
	printf("%d\n", fd);
	fd = open("./C/G/i", O_WRONLY);
	printf("%d\n", fd);
}
