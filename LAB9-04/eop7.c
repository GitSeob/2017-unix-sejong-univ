#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int data[10]={0};
	int i,fd;
	fd = open("test2", O_RDONLY);
	
	read(fd, &data, sizeof(int)*5 );
	
	for(i=0;i<10;i++){
		printf("%d\n",data[i]);
	}
	printf("done\n");

	return 0;
}
