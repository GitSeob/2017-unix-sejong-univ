#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	int i, fd, k, k1, data1[10], data2[10];
	
	fd = open("data3", O_RDWR|O_CREAT, 0600);

	for(i=0;i<10;i++){
		scanf("%d", &data1[i]);
	}
	k = lseek(fd, 0, SEEK_CUR);
	printf("fuck = = %d\n",k);

	for(i=0;i<5;i++){
        	write(fd, data1+i, sizeof(int));
		k = lseek(fd, sizeof(int), SEEK_CUR);
		printf("lseek = %d\n", k);
        }

	//lseek(fd, 0, SEEK_SET);
	lseek(fd, -9*sizeof(int), SEEK_CUR);

	for(i=5;i<10;i++){
                write(fd, data1+i, sizeof(int));
		k = lseek(fd, sizeof(int), SEEK_CUR);
       		printf("lseek = %d\n", k);
	 }


	//for(i=5;i<10;i++){
	//	write(fd, &data1[i], sizeof(int));
	//	k = lseek(fd, -(sizeof(int)), SEEK_CUR);
	//	printf("lseek = %d\n", k);       
        //}
        //
        //여기서 포인터가 왼쪽으로 가지 않는 문제가 발생하여 위의 코드로 응급처치만 한 상태

	k1 = lseek(fd, 0, SEEK_SET);
	printf("lseek = %d\n", k1);
	
	read(fd, data2, sizeof(int)*10);

	for(i=0;i<10;i++){
		printf("%-5d", data1[i]);
	}
	printf("\n");
	for(i=0;i<10;i++){
                printf("%-5d", data2[i]);
        }
	printf("\ndone\n");

	return 0;
}
