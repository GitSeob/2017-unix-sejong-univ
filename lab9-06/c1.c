#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	struct stat buf;

	stat("t1.c", &buf);
	printf("%o %ld %ld",buf.st_mode&0777 ,buf.st_nlink, buf.st_size);

	return 0;
}
