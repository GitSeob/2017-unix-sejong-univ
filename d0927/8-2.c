#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void catchusr(int);

void do_child(int i, int *cid){
	int j, pid;
	static struct sigaction act;
	
	act.sa_handler = catchusr;
	sigaction(SIGUSR1, &act, NULL);

	if(i<4)
		pause();

	pid = getpid();
	for(j=0;j<5;j++){
		printf("child %d ..... \n", pid);
		sleep(1);
	}		

	if(i>0)
		kill(cid[i-1], SIGUSR1);

	exit(0);
}

int main(){
	int i,status;
	pid_t pid[5];

	for(i=0;i<5;i++){
		pid[i] = fork();
		if(pid[i] == 0){
			do_child(i, pid); //pid의 배열data 가져감 -- 자신전의 pid에게 시그널
		}
	}

	for(i=0;i<5;i++){
		wait(&status);
	}

	exit(0);
}

void catchusr(int signo){
	printf(".................. catch SIGUSR1 : %d\n", signo);
}