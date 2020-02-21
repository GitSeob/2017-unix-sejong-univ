#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){
	char fn[128], uptime[128];
	int i, n;
	struct stat buf;

	n = read(0, fn, 128);
	fn[n-1]='\0';	

	//printf("%s\n", fn);
	//printf("%d\n", n);	

	stat(fn, &buf);

	//stat("c4.c", &buf);
	//printf("check\n");
	//printf("%s\n", ctime(&buf.st_ctime));

	//printf("%s\n", uptime);

	printf("%o  %ld  %ld  %ld  %ld  ", buf.st_mode&0777, buf.st_nlink, buf.st_uid, buf.st_gid, buf.st_size);
	strcpy(uptime, ctime(&buf.st_mtime));
	n = strlen(uptime);
	uptime[n-1]='\0';
	printf("%s  ", uptime);
	printf("%s\n", fn);

// ctime 문제..(?) read 키보드 입력 문제//
	
	


	printf("done\n"); 

        return 0;
}

