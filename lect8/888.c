#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

void ls_m(char* s);
void mkdir_m(char* s);
void exec_m(char* s);
void vi_m(char* s);
void cat_m(char* s);

int main(void){
	int mode = 0;
	char fileName [100]= {0};
	char *realName;
	//char *commend;
	//char cut[] = {" "};
	while(1){

		printf("> ");
		gets(fileName);

		 if(fileName[0] == 'l' && fileName[1] == 's' && fileName[2] == '\0'){
	 		ls_m(realName);
		 }
	 	else if(fileName[0] == 'm' && fileName[1] == 'k' && fileName[2] == 'd' && fileName[3] == 'i' && fileName[4] == 'r' && fileName[5] == ' '){
	 		strcpy(realName,&fileName[6]);
	 		mkdir_m(realName);
		 }

		 else if(fileName[0] == '.'){
		 	exec_m(fileName);
		 }
	
	 	else if(fileName[0] == 'v' && fileName[1] == 'i' && fileName[2] == ' '){
	 		strcpy(realName,&fileName[3]);
	 		vi_m(realName);
	 	}
	 	else if(fileName[0] == 'c' && fileName[1] == 'a' && fileName[2] == 't' && fileName[3] == ' '){
	 		strcpy(realName,&fileName[4]);
		 	cat_m(realName);
		 }
	}	

	return 0;
}

void ls_m(char *s){
        DIR *dp;
        struct dirent *dent;
        char *cwd;
        cwd = getcwd(NULL, BUFSIZ);
                if((dp = opendir(cwd)) ==NULL ){
                        printf("open error");
                        exit(1);
                }
						 
                while((dent = readdir(dp))){
                        if(dent->d_name[0] =='.')
                                continue;
                       printf("%s   ", dent->d_name);
                }
                printf("\n");
                closedir(dp);
					
}

void mkdir_m(char *s)
{
	mkdir(s, 0600);
}

void exec_m(char *s)
{
	execl(s, s, "0", (char *) 0);
}

void vi_m(char* s){
	char text[300] = {0};
	char text2[300] = {0};
	int fd,fileState,tmpRead;
	int n;

	fileState = access(s,F_OK);
	
	if(fileState == 0){
		fd = open(s,O_RDWR);
		do{
			tmpRead = read(fd,text,300);
			write(1, text, tmpRead);
		}while(tmpRead >= 300);
		while(1){
			//gets(text2);
			n = read(0, text, 128);
			if(strncmp(text,"quit",4) == 0)
				return;

			//text2[strlen(text2)] = '\n';
			write(fd,text,n);
		}
	}
	else{
		fd = open(s,O_WRONLY|O_CREAT,0777);
		while(1){
			//gets(text);
			n = read(0, text, 128);
			if(strncmp(text,"quit",4)==0)
				return;

			//text[n] = '\n';
			write(fd,text,n);
		}
	}
}

void cat_m(char *s){
	int fd, getn;
	char buf[512] = {0};

	fd = open(s, O_RDONLY);
	do{
		getn = read(fd, buf, sizeof(char)*512);
		write(1, buf, getn);
	}
	while(getn>0);
}

