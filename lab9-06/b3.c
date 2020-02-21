#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>	//ctime을 쓰기위한 해더
#include <dirent.h>	//

int main(){
	DIR *dp;	//directory pointer를 저장하기 위한 장소..
	struct dirent *d;	//directory 정보들을 저장할 구조체 포인터
	struct stat status;	//file, directory 정보들을 저장한 stat 포인터
	char uptime[128];	//ctime함수를 이용해 저장할 장소
	int n;		//uptime의 문자열 끝의 \n를 제거하기 위해 정수형 변수 사용.

	dp = opendir(".");
	while(d = readdir(dp)){
		if(d->d_name[0]!='.'){	//현재 디렉토리( . )와 전 디렉토리 ( .. )를 제외하고 출력.
			stat(d->d_name, &status);	//
			printf("%o  ", status.st_mode&0777);
			printf("%ld  ", status.st_nlink);
			printf("%ld  ", status.st_uid);
			printf("%ld  ", status.st_gid);
			printf("%ld  ", status.st_size);

			strcpy(uptime, ctime(&status.st_mtime));
			n = strlen(uptime);
			uptime[n-1]='\0';
			printf("%s  ", uptime);
			printf("%s     \t", d->d_name);
			// printf("%u \n", d->d_type);
			// if(strcmp(&d->d_type, "8")==0)
			// 	printf(":: F");
			//printf("%s\n", status.st_rdev);
			if(S_ISREG(status.st_mode)){
				printf(" :: F");
			}
			else printf(" :: D");

			printf("\n");
		}
	}
	return 0;
}
