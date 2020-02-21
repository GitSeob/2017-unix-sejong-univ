#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int main(){
	DIR *dp;
	struct dirent *d;

	dp = opendir(".");
	d = readdir(dp);
	while(d!=NULL){
		printf("%ld : %s\n", d->d_ino, d->d_name);
	}
	
	return 0;
}
