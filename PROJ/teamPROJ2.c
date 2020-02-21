#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>

void ls_m(char* s);
void mkdir_m(char* s);
void exec_m(char* s);
void vi_m(char* s);
void cat_m(char* s);
void cd_m(char* s);

int main(void){
	char in[50], *res;
	char *inst[6] = {"ls","mkdir","cat","vi","cd","./"};
	char *currentPath;
	int i, flag, pid,status;
	void (*f[6])(char*) = {ls_m, mkdir_m, cat_m, vi_m, cd_m, exec_m};
	static struct sigaction sig;

	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);

	while(1){
		currentPath = getcwd(NULL,256);
		printf("%s> ",currentPath);
		gets(in);
		res = strtok(in, " ");
		
		if(strcmp(res, "exit")==0){
			break;
		}

		else{
			for(i=0; i<6; i++){
				flag = 0;
				if(i == 5){
					if(strncmp(res,inst[i],2) == 0){
						flag = 1;
						break;
					}	
				}

				else if(!strcmp(res,inst[i])){
					flag = 1;
					break;
				}
			}

			if(flag == 1){
				if(i == 4)
					f[i](res);

				else{
					pid = fork();

					if(pid == 0){
						sig.sa_handler = SIG_DFL;
						sigaction(SIGINT, &sig, NULL);

						f[i](res);
					}

					else{
						wait(&status);
					}
				}
			}
		}
	}

	exit(0);

}

void cd_m(char *s){
	s = strtok(NULL," ");
	chdir(s);
}

void ls_m(char *s){
	s = strtok(NULL," ");
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
            printf("%s\n", dent->d_name);
        }

    closedir(dp);

	exit(0);					
}

void mkdir_m(char *s)
{
	s = strtok(NULL," ");
	mkdir(s, 0777);
	exit(0);
}

void exec_m(char *s)
{
	execl(s, s, "0", (char *) 0);
}

void vi_m(char* s){
	s = strtok(NULL," ");
	char text[512] = {0};
	char text2[512] = {0};
	int fd,fileState,tmpRead;
	int n;

	fileState = access(s,F_OK);
	
	if(fileState == 0){
		fd = open(s,O_RDWR);

		do{
			tmpRead = read(fd,text,512);
			write(1, text, tmpRead);
		}while(tmpRead >= 512);

		while(1){
			n = read(0, text, 512);

			if(strncmp(text,"quit",4) == 0)
				exit(0);

			write(fd,text,n);
		}
	}

	else{
		fd = open(s,O_WRONLY|O_CREAT,0777);
		while(1){
			n = read(0, text, 512);

			if(strncmp(text,"quit",4)==0)
				exit(0);

			write(fd,text,n);
		}
	}

	exit(0);
}

void cat_m(char *s){
	s = strtok(NULL," ");
	int fd, getn;
	char buf[512] = {0};

	fd = open(s, O_RDONLY);

	do{
		getn = read(fd, buf, sizeof(char)*512);
		write(1, buf, getn);
	}

	while(getn>0);

	exit(0);
}
