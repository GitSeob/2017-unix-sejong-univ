#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(){
	DIR *dp;
	struct dirent *d;
	struct stat st;	
	int fd, rfd, getdn;
	int n1, n2;
	char readdata[512];	

	fd = open("merge", O_WRONLY|O_CREAT|O_TRUNC, 0200);

	dp = opendir(".");
	
	while(d=readdir(dp)){
		stat(d->d_name, &st);
		n1 = (S_IRUSR&st.st_mode||S_IRGRP&st.st_mode||S_IROTH&st.st_mode);
		n2 = !(S_IXUSR&st.st_mode||S_IXGRP&st.st_mode||S_IXOTH&st.st_mode);
		if(S_ISREG(st.st_mode)&&n1&&n2){
			rfd =open(d->d_name, O_RDONLY);
			while(getdn = read(rfd, readdata, 512)){
				write(fd, readdata, getdn);
			}
		}
	}
	
	return 0;
}
//실행 파일이 아닌지도 체크해야함
