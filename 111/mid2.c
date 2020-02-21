#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
        int fd;

        fd=open("data2", O_RDWR);

	printf("%d\n", lseek(fd, 0, SEEK_END));

        lseek(fd, +5, SEEK_END);
        printf("%d\n", lseek(fd, 0, SEEK_CUR)); 
        printf("%d\n", lseek(fd, 0, SEEK_END));	

        lseek(fd, +5, SEEK_END);
        write(fd, "A", 1);
        printf("%d\n", lseek(fd, 0, SEEK_CUR));	
        printf("%d\n", lseek(fd, 0, SEEK_END));

        return 0;
}
