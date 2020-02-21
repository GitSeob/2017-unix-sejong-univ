#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	char ffn[100],sfn[100];
	printf("input file name : ");
	scanf("%s", ffn);
	printf("input file name : ");
        scanf("%s", sfn);
	link(ffn, sfn);
	printf("done\n"); 

        return 0;
}

