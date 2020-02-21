#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	char* argv[]={"test01","abc","def","ghi",(char *)0};

	execv("./test01",argv);

	exit(0);
	//return 0;
}
