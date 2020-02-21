#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <signal.h>

#define MSGSIZE 6
#define N 3

char *msg1 = "hello";
char *msg2 = "bye!!";
void do_parent(int[][2]);
int do_child(int[]);

int main(){
	int pip[N][2];
	int i;

	for(i=0;i<N;i++){
		pipe(pip[i]);
		if(fork() == 0)
			do_child(pip[i]);
	}
	do_parent(pip);
	for(i=0;i<N;i++)
		wait(0);


	exit(0);
}

void do_parent(int p[N][2]){
	char buf[MSGSIZE], ch;
	fd_set set, master;
	int i, j, k;

	for(i=0;i<N;i++)
		close(p[i][1]);

	FD_ZERO(&master);
	//fdset bit를 0으로 초기화

	for(i=0;i<N;i++)
		FD_SET(p[i][0], &master);
		//fdset의 bit를 1로 설정
	while(set=master, select(p[2][0]+1, &set, NULL, NULL, NULL)>0){
		//mask를 지우기 떄문에 master를 보호하고 set으로 master복사 하여 사용
		//꼭 pipe +1 을 해줘야함
		for(i=0;i<N;i++){
			if(FD_ISSET(p[i][0], &set)){
			//fdset의 bit가 1인지 검사 = pipe에 data가 있는지
				if(read(p[i][0], buf, MSGSIZE)>0)
					//상대편이 종료시 무한으로 0을 return하기 떄문에
					//size를 check해서 출력
					printf("MSG from %d = %s\n",i, buf);
			}
		}
	
		if(waitpid(-1, NULL, WNOHANG) == -1)
			return;
		//살아있는 child process가 업슨ㄴ데 wait면 return해서 종료
	}
}
	
int do_child(int p[2]){
	int count;

	close(p[0]);

	for(count=0;count<2;count++){
		write(p[1], msg1, MSGSIZE);
		sleep(getpid()%4);
	}

	write(p[1], msg2, MSGSIZE);

	exit(0);
}

