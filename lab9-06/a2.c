#include <stdio.h>
#include <unistd.h>

int main(){
	char ch[100] = {0};

	mkdir("T1", 0700);
	chdir("T1");
	mkdir("T2", 0700);
        chdir("T2");
	mkdir("T3", 0700);
        chdir("T3");
	//chdir 명령어는 프로세스 실행중에만 directory 이동,, 프로세스 종료면 실행전 그대로

	getcwd(ch, 99);
        printf("%s\n", ch);

	return 0;
}
