#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	execlp("test02","test02","abc","def","ghi",(char*)0);

	return 0;
}