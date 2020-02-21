#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void catchusr(int);

void do_child(int i){
	int j,pid;
	static struct sigaction act;
	
	act.sa_handler==catchusr;
	sigaction(SIGUSR1, &act, NULL);	

	printf("%d-th child is created ... \n", i);

	pause();	

	pid = getpid();
	for(j=0;j<3;i++){
		printf("child %d ........\n",pid);
		sleep(1);
	}
	// signal 받으면 process id 3번 출력
	// for(j=0;j<3;j++){
	// 	printf("...........pid : %d\n", getpid());
	// }

	exit(0);
}

int main(){
	int i, k, status;
	pid_t pid[3];

	for(i=0;i<3;i++){
		pid[i] = fork();
		if(pid[i]==0){
			do_child(i);
		}
	}
	//1초씩 sleep 하면서 child들에게 sigusr1 보내기
	for(i=0;i<5;i++){
		sleep(1);
		kill(pid[i], SIGUSR1);
	}	

	for(i=0;i<3;i++){
		k=wait(&status);
		printf("child #%d is terminated...\n", k);
	}

	exit(0);
}

void catchusr(int signo){
	printf(".................. catch SIGUSR1 : %d\n", signo);
}
