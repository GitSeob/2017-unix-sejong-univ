#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
	struct stat *buf;

	stat("p1.c", buf);
	printf("%o %ld\n%ld",buf.st_mode#0777 ,st_nlink, buf.st_size);

	return 0;
}
