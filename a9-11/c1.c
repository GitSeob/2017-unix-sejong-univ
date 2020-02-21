#include <unistd.h>

int main(){

	link("test1", "test2");
	link("test1", "A/B/C/test3");

	return 0;
}
