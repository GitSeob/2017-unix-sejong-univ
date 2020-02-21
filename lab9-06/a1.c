#include <stdio.h>
#include <unistd.h>

int main(){
	char ch[100] = {0};

	getcwd(ch, 99);
	printf("%s\n", ch);

	return 0;
}
