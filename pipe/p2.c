#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

do_child(int id, int p[3][2]){
	int i, in=2, pid = getpid();
	if(id==0){
		close(p[id][1]);
		read(p[id][0], &in, sizeof(int));
	}
	else if(id == 1){
		read(p[id][0], &in, sizeof(int));
	}
	else{
		close(p[id][0]);
	}
	for(i=0;i<5;i++){
		sleep(1);
		printf("%d is .......%d\n", id, pid);
	}
	if(id!=0){
		write(p[id-1][1], &in, sizeof(int));
	}
	exit(0);
}

int main(){
	int p[3][2], i;
	//파이프 2개로 수정

	for(i=0;i<3;i++){
		pipe(p[i]);
		if(fork() == 0){
			do_child(i, p);
		}
	}
	for(i=0;i<3;i++){
		close(p[i][0]);
		close(p[i][1]);
	}

	for(i=0;i<3;i++){
		wait(0);
	}

	printf("parent is down\n");
	exit(0);
}
