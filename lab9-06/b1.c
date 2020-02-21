#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>	//디렉토리 구조체를 위해

void change_directory(char *name){
	chdir(name);
	//cd명령수행
}
void list(){
	DIR *dp;
        struct dirent *d;
	dp = opendir(".");
	
	while(d = readdir(dp)){
		//d = readdir(dp);
		if(d->d_name[0]!='.'){
			printf("%ld : %s\n", d->d_ino, d->d_name);
		}
	}
	//closedir(".");
	//ls명령수행
}


int main(){
	char name[50];
	char ch[128];

	while(1){
		getcwd(ch, 99);
        	printf("%s\n", ch);	
		//현재 working directory 표시
		scanf("%s", name);
		if(strcmp(name, "cd")==0){
			scanf("%s", name);
			change_directory(name);
		}
		else if(strcmp(name,"ls")==0)
			list();
		else if(strcmp(name,"exit")==0)
			break;
		else break;
	}	

	printf("done\n"); 

        return 0;
}

