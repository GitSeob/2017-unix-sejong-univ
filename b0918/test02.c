#include <stdio.h>

int main(int argc, char **input){
	int i;
	i=1;
	//printf("%d\n", argc);
	while(input[i]!=NULL){
		printf("%s  ", input[i]);
		i++;
	}
	printf("\n");


	return 0;
}