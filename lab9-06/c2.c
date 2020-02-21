#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int okn;
	okn = access("data1", F_OK|R_OK|W_OK);
	printf("%d\n", okn);

        return 0;
}

