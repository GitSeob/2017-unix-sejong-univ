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

#define N 3

void do_child(int i, int p[N][2]){
	int j;
	char buf = 'a';
	for(j=0;j<N;j++){
		if(j!=i){
			close(p[j][0]);//필요없는 읽기 pipe 닫기
			close(p[j][1]);//필요없는 쓰기 pipe 닫기
		}
	}

	read(p[i][0], &buf, 1);
	//기본적으로 blocking, 읽은 데이터는 사라진다.
	
	printf("hi\n");

	exit(0);
}

int main(){
	int p[N][2], i, j, num;
	char buf = 'a';
	for(i=0;i<N;i++){
		pipe(p[i]);
		if(fork()==0){
			do_child(i, p);
		}
		else{
			sleep(1);
			write(p[i][1], &buf, 1);//해당 pipe에 데이터 전송
		}
	}

	for(i=0;i<N;i++)
		wait(0);

	exit(0);
}
