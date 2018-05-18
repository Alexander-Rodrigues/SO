#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dataStructs.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Use ./program <filepath>\n");
        return 0;
    }
    int fil = open(argv[1], O_RDWR);
    if (fil < 0) {
        perror("Error opening file");
        return fil;
    }
    int n = 1; char buf[256] = "";
    while (n > 0) {
        n = read(fil,buf,256);
        write(1,buf,n);
        printf("jg\n");
    }
    //int fil = open(argv[1])
}
