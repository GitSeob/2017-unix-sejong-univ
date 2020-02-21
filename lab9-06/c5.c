#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	char syfn[100], realname[100];
	struct stat buf;
	printf("input file name : ");
        scanf("%s", syfn);
	lstat(syfn, &buf);

	printf("sym file info\n");
	printf("%o / %ld :: %s\n", buf.st_mode&0777, buf.st_size, syfn);
	readlink(syfn, realname, 100);
	stat(syfn, &buf);
	printf("%o / %ld :: %s is real name\n", buf.st_mode&0777, buf.st_size, realname);

	printf("done\n"); 

        return 0;
}

