#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char ch = 'X';
	int i,fd;
	fd = open("test1", O_WRONLY|O_CREAT, 0600);
	for(i=0;i<10;i++){
		write(fd, &ch, 1);
	}
	
	printf("done\n");

	return 0;
}
