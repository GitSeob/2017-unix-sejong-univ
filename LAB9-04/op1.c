#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char ch = 'X';
	int fd;
	fd = open("test1", O_WRONLY|O_CREAT, 0600);
	write(fd, ch, sizeof(char)*10);
	
	printf("done\n");

	return 0;
}
