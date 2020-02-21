#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int nn, i, fd, data1[10], data2[10];
	for(i=0;i<10;i++){
		printf("input num : "); 
		scanf("%d", &data1[i]);
	}
	fd = open("data1", O_RDWR|O_CREAT, 0600); //파일 생성을 적어주지 않아서 에러가 발생하였다 .. 참고 
	write(fd, data1, sizeof(int)*10);
	nn = lseek(fd, 0, SEEK_CUR);
        printf("%d\n", nn);

	nn = lseek(fd, 0, SEEK_SET);
	printf("%d\n", nn);
	read(fd, data2, sizeof(int)*10);

	for(i=0;i<10;i++){
		printf("%-5d", data1[i]);
	}
	printf("\n");
	for(i=0;i<10;i++){
		printf("%-5d", data2[i]);
	}
	printf("\n");
	
	return 0;
} 
