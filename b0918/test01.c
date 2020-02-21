#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid = getpid();

	printf("pid : %ld  | ", pid);
	printf("gpid : %ld  | ", getpgrp());
	printf("session id : %ld\n", getsid(pid));

	return 0;
}