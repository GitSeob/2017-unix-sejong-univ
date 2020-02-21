#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
        int fd,i;
        char ch = 'S';
	int cc;

        fd = open("data2",O_WRONLY|O_CREAT|O_APPEND);
	
	cc = lseek(fd, 0, SEEK_CUR);
	printf("%d\n",cc);
	cc = lseek(fd, -2, SEEK_END);
	printf("%d\n",cc);
        write(fd, &ch, sizeof(char));

        return 0;
}
// 여준이코드
// 원래 여준이 코드는 오픈할 때 파일 포인터가 맨 앞을 가르키고 있는데 -2를 하면 core dump가 뜸 ..
