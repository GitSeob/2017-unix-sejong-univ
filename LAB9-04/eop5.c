#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char ch = 'K';
	int i,fd;
	fd = open("test1", O_WRONLY|O_TRUNC, 0600);
	for(i=0;i<3;i++){
		write(fd, &ch, 1);
	}	
	
	printf("done\n");

	return 0;
}