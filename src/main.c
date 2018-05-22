#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dataStructs.h>
#include <transform.h>
#include <processor.h>

int main(int argc, char *argv[])
{
    LIST l = list_new();
    int r = noteToList(argc, argv, l);
    printf("--------------------//---------------------\n\n");
    list_process(l);
    //list_print(l);
    return r;
}
