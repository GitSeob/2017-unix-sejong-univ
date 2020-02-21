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
	int fd;
	int rfd, getdn;
	char readdata[512];	

	dp = opendir(".");
	fd = open("merge", O_WRONLY|O_CREAT|O_TRUNC, 0200); //permission때문에 merge가 자신을 읽어서 쓸수도 있음 - 무한루프...
       	while((d = readdir(dp))){
       	//d = readdir(dp);
		if(d->d_name[0]!='.'){
			//fd = open("merge", O_WRONLY|O_CREAT|O_APPEND, 0600);
			stat(d->d_name, &st);
                	if(S_ISREG(st.st_mode)){
				if(S_IRUSR&st.st_mode)
				{
					if(S_IXUSR&st.st_mode){
						continue;
					}
					else{
						rfd = open(d->d_name, O_RDONLY);
						do{
							//fd = open("merge", O_WRONLY|O_CREAT|O_TRUNC, 0600);
							getdn = read(rfd, readdata, sizeof(char)*512);	
							write(fd, readdata, sizeof(char)*getdn);
						}
						while( getdn > 0);
					}
				}
			}
		}
	}
	return 0;
}
//실행 파일이 아닌지도 체크해야함
