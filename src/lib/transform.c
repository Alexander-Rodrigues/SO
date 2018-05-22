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

int noteToList(int argc, char *argv[], LIST list)
{
    if(argc<2) {printf("Arguments missing! Use ./program <filepath>\n"); exit(-1);}
    FILE* fil = fopen(argv[1], "r");
    if(fil==NULL) {perror("Error opening file!\n"); exit(-1);}
    char line[1024];
    char command[1024];
    int* quantity=0;
    while(fgets(line, sizeof(line), fil) != NULL)
    {
        if(sscanf(line, "$%d| %[^\t\n]", quantity, command)==2) {list_add(list, *quantity, command, NULL);}
        else if(sscanf(line, "$| %[^\t\n]", command)==1) {list_add(list, 1, command, NULL);}
        //else if(sscanf(line, "$ %[^\t\n] |", command)==1) {printf("%s\n", command);}
        else if(sscanf(line, "$ %[^\t\n]", command)==1) {list_add(list, 0, command, NULL);}
        else {printf("Error reading file!\n"); exit(-1);}
    }
    list_print(list);
    fclose(fil);
    return 0;
}

int listToNote(LIST list)
{
	
}