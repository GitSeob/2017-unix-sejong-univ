#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int i;

	for(i=0; i<5; i++){
		printf("%s\n", argv[2]);
		sleep(1);
	}

	exit(atoi(argv[1]));
}
