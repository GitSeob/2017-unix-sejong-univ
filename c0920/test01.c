#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int i,j ;
	for(j=1; j<argc;j++){
	for(i=0; i<3;i++){
		printf("%s\n", argv[j]);
	}
}
	return 0;
}