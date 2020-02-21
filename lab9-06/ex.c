#include <sys/stat.h>
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
//#include <stdlib.h>

int list(const char *name, const struct stat *status, int type) {
	//char chanptr
	//unsigned long int moden = strtoul("755", NULL, 8);
	if (type==FTW_NS)
		return 0;
	if (type==FTW_F){
		if( S_IXUSR&status->st_mode || S_IXGRP&status->st_mode || S_IXOTH&status->st_mode){
			printf("FILE   :: %-30s \t %ld\t%o\n", name, status->st_size, status->st_mode&0777);
		//파일 중에 실행 파일인 것만 출력
		}	
	}
	else if(type==FTW_D || type==FTW_DNR)
		printf("DIRECT :: %-30s \t %ld\t%o\n", name, status->st_size, status->st_mode&0777);
	return 0;
}
int main(){
	ftw("..", list, 1);

	return 0;
}
