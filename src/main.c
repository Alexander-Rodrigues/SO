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
    if (fil < 0) {
        perror("Error opening file");
        return fil;
    }
    LIST l = list_new();
    l = example(l);
    list_print(l);

}
