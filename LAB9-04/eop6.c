#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	char ch = 'K';
	int i,fd;
	fd = open("test3", O_WRONLY|O_CREAT|O_EXCL, 0640);
	if(fd == -1){
		printf("error\n");
	}
	else{
		for(i=0;i<10;i++){
			write(fd, &ch, 1);
		}
	}
	
	printf("done\n");

	return 0;
}
