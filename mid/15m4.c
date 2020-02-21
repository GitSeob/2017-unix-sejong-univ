#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>
#include <stdlib.h>
#include <string.h>

void copy_file(){
	printf("copy\n");
}

int backup(const char *name, const struct stat *sptr, int type){
	char backup_dir[50] = "./TEMP/";

	strcat(backup_dir, name);

	if(type==FTW_D){
		if(strcmp(name,".")!=0 && strcmp(name, "./TEMP")!=0){
			mkdir(backup_dir, 0700);
		}
	}
	else if(type == FTW_F){
		copy_file(name, backup_dir);
	}


	return 0;
}

int main(){
	mkdir("TEMP", 0700);
	ftw(".", backup, 1);	

	exit(0);
}