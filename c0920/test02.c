#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	execl("./test01","test01","abc","def","ghi",(char*)0);

	//return 0;
	exit(0);
}

