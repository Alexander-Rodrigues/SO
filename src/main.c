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
    LIST list = list_new();
    noteToList(argc, argv, list);
    list_print(list);
    list_process(list);
    list_print(list);
    return 0;
}
