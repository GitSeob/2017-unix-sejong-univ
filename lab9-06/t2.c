#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	int fd, i;
	char chw = 'W',cht = 'T', chs = 'S', chx = 'X', chy = 'Y', chz = 'Z';
	int chside;


	fd = open("data2", O_RDWR|O_CREAT|O_TRUNC, 0600);
	
	for(i=0;i<10;i++){
		write(fd, &chx, sizeof(char));
	}
	chside = lseek(fd, 0, SEEK_SET);
	printf("%d\n", chside);
	chside = write(fd, &chy, sizeof(char));
	printf("%d\n", chside);

	chside = lseek(fd, 0, SEEK_END);
	printf("%d\n", chside);
	chside = write(fd, &chy, sizeof(char));
	printf("%d\n", chside);

	lseek(fd, 0, SEEK_SET);

	for(i=1;i<8;i+=2){
		lseek(fd, i, SEEK_SET);
		write(fd, &chz, sizeof(char));	
	}
	chside = lseek(fd, 14, SEEK_SET);
	printf("%d\n", chside);
	write(fd, &cht, sizeof(char));
	chside = lseek(fd, -2, SEEK_END);
	write(fd, &chs, sizeof(char));
	printf("%d\n", chside);
	chside = lseek(fd, -2, SEEK_CUR);
	printf("%d\n", chside);
	write(fd, &chw, sizeof(char));

	printf("done\n");

	return 0;
}
