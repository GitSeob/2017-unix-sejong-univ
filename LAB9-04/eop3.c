#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char ch = 'Y';
	int i,fd;
	fd = open("test1", O_WRONLY);
	for(i=0;i<5;i++){
		write(fd, &ch, 1);
	}
	
	printf("done\n");

	return 0;
}
