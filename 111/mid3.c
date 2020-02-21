#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
        char buf[512];

        symlink("./B/E", "TEMP");
        mkdir("./TEMP/F", 0777);
        chdir("./TEMP/F");
        getcwd(buf, 512);
        printf("%s\n", buf);

        return 0;
}
