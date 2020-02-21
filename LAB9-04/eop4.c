#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
	char ch = 'Z';
	int i,fd;
	fd = open("test1", O_WRONLY|O_APPEND, 0600);
	for(i=0;i<5;i++){
		write(fd, &ch, 1);
	}
	
	printf("done\n");

	return 0;
}
