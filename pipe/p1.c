#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid[3], p[3][2], i, j, num;
	for(i=0;i<3;i++){
		pipe(p[i]);
		if(fork() == 0){
			close(p[i][1]);
			while(1){
				read(p[i][0], &num, sizeof(int));
				if(num == -1){
					printf("%d got a value of -1, so GOOD BYE\n", getpid());
					exit(0);
				}
				else{
					printf("%d : %d\n",getpid(), num);
				}
			}
		}
		else{
			close(p[i][0]);
		}
	}
	
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			scanf("%d", &num);
			write(p[j][1], &num, sizeof(int));
		}
	}
	num = -1;

	for(i=0;i<3;i++){
		write(p[i][1], &num, sizeof(int));
	}

	for(i=0;i<3;i++){
		wait(0);
	}

	exit(0);
}
// 수정필요
// 각child 에서 불필요한 읽기 파이프 close 해야함
