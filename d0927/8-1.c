#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void catchusr(int);

void do_child(int i){
	int j, pid;
	static struct sigaction act;
	
	act.sa_handler = catchusr;
	sigaction(SIGUSR1, &act, NULL);

	printf("%d-th child is created ... \n", i);

	pause();

	pid = getpid();
	for(j=0;j<3;j++){
		printf("child %d ..... \n", pid);
		sleep(1);
	}		

	exit(0);
}

int main(){
	int i, k ,status;
	pid_t pid[3];

	for(i=0;i<3;i++){
		pid[i] = fork();
		if(pid[i] == 0){
			do_child(i); 
		}
	}

	for(i=0;i<3;i++){
		sleep(1);
		kill(pid[i], SIGUSR1);
	}	

	for(i=0;i<3;i++){
		k = wait(&status);
		printf("cild #%d is terminated...\n", k);
	}

	exit(0);
}

void catchusr(int signo){
	printf(".................. catch SIGUSR1 : %d\n", signo);
}