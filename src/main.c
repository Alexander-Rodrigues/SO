#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dataStructs.h>

#define SIZE 256

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Arguments Missing! Use ./program <filepath>\n");
        return -1;
    }
    int fil = open(argv[1], O_RDWR);
    if(fil < 0) {perror("Error opening file!"); return fil;}
    int n = 1;
    char buf[SIZE];
    while (n > 0)
    {
        n = read(fil, buf, SIZE);
        write(1, buf, n);
    }
    if(n<0) {perror("Error reading file!"); return n;}
    return 0;
}
