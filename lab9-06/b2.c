#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>	//ctime을 쓰기위한 해더
#include <dirent.h>	// 
#include <ftw.h>

int lsl(const char *name, const struct stat *status, int type){
	char uptime[128];
	int n;
	
	if(type == FTW_NS)
		return 0;
	if(type == FTW_F)
		printf("F :: ");
	else if(type == FTW_D)
		printf("D :: ");

	//stat(name, status);
	
    printf("%o  %ld  %ld  %ld  %ld  ", status->st_mode&0777, status->st_nlink, status->st_uid, status->st_gid, status->st_size);
    strcpy(uptime, ctime(&status->st_mtime));
    n = strlen(uptime);
    uptime[n-1]='\0';
    printf("%s  ", uptime);
    printf(": %s\n", name);

	return 0;
}

int main(){
	ftw(".", lsl, 1);	

	printf("done\n"); 

        return 0;
}

