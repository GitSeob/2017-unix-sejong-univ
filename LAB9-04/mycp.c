#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	char ffn[100], sfn[100];
	int fd1, fd2, checknum;
	char fdata[100];
	int getdatanum;

	printf("input first file name : ");
	scanf("%s", &ffn);
	printf("input second file name : ");
	scanf("%s", &sfn);

	fd1 = open(ffn, O_RDONLY);
	if(fd1 == -1) printf("not find file\n");
	else{
		getdatanum = read(fd1, fdata, sizeof(char)*100);
		fd2 = open(sfn, O_WRONLY|O_CREAT|O_EXCL, 0644);
		if(fd2 == -1){
			printf("Already existing file name..\nWant Continue - input 1 or Want Stop - input - other number\ninput number : ");
			scanf("%d", &checknum);
			if(checknum == 1){
				fd2 = open(sfn, O_WRONLY|O_CREAT|O_TRUNC, 0644);
				lseek(fd1, 0, SEEK_SET); //앞에서 read해줘서 fpointer 다시 처음으로 이동
				do{
					getdatanum = read(fd1, fdata, sizeof(char)*100);
					//lseek(fd2, 0, SEEK_END);
					//fd2 = open(sfn, O_WRONLY|O_APPEND);
					write(fd2, fdata, sizeof(char)*getdatanum);				
				} 
				while(getdatanum > 0);
			}
			else{
				printf("Don't copy file\nBYE\n");	
			}
		}
		else{
			lseek(fd1, 0, SEEK_SET);
			do{
				getdatanum = read(fd1, fdata, sizeof(char)*100);
				write(fd2, fdata, sizeof(char)*getdatanum);
			}
			while(getdatanum > 0);
		}
	}
	return 0;
} // 처음의 100개 날아감 .. 코드의 오류 -> 해결
