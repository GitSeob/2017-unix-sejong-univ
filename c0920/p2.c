#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	int i, status;
	pid_t pid;

	for(i=0;i<3;i++){
		pid = fork();
		if(pid==0&&i==0){
			execl("./p2-a", "p2-a", "1", "abcde", (char *)0);
		}
		else if(pid==0&&i==1){
			execl("./p2-b", "p2-b", "2", (char *)0);
		}
		else if(pid == 0){
			execl("./p2-c", "p2-c", "3", (char *)0);
		}
	}
	for(i=0; i<3; i++){
		wait(&status);
		if (WIFEXITED(status)){
			printf(".......%d\n", WEXITSTATUS(status));
		}
	}

	exit(0);
}
