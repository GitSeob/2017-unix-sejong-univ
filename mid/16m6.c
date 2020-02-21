#include <stdio.h>
#include <dirent.h>
#include <ftw.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int del_dir(const char *name, const struct stat *sptr, int type){
	int k;
	struct dirent *d;
	DIR *dp;

	k = 0;

	if(type == FTW_D){
		dp = opendir(name);
		while(d = readdir(dp)){
			k++;
		}
	}
	if(k==2){
		rmdir(name);
		printf("%s is removed .. \n", name);
	}

	return 0;
}

int main(){
	ftw(".", del_dir, 1);

	return 0;
}