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

void noteToList(int argc, char *argv[], LIST list)
{
    if(argc<2) {printf("Arguments missing! Use ./program <filepath>\n"); exit(-1);}
    FILE* fil = fopen(argv[1], "r");
    if(fil==NULL) {perror("Error opening file!\n"); exit(-1);}
    char line[1024];
    char command[1024];
    int* quantity=0;
    while(fgets(line, sizeof(line), fil) != NULL)
    {
        if(sscanf(line, "$%d| %[^\t\n]", quantity, command)==2) {list_add(list, *quantity, command, NULL,0);}
        else if(sscanf(line, "$| %[^\t\n]", command)==1) {list_add(list, 1, command, NULL,0);}
        //else if(sscanf(line, "$ %[^\t\n] |", command)==1) {printf("%s\n", command);}
        else if(sscanf(line, "$ %[^\t\n]", command)==1) {list_add(list, 0, command, NULL,0);}
        else {printf("Invalid notebook format!\n"); exit(-1);}
    }
    //list_print(list);
    fclose(fil);
}

void listToNote(int argc, char *argv[], LIST list)
{
	THING thing;
	int ref;
	char* output;
	char* params;
	int size = list_size(list);
	if(argc<2) {printf("Arguments missing! Use ./program <filepath>\n"); exit(-1);}
	FILE* fil = fopen(argv[1], "w");
	if(fil==NULL) {perror("Error opening file!\n"); exit(-1);}
	for(int i=0;i<size;i++)
	{
		thing = list_get_thing(list, i);
		ref = thing_get_ref(thing);
		params = thing_get_params(thing);
		output = thing_get_output(thing);
		if(ref==0)
		{
			fprintf(fil, "$ %s\n", params);
		}
		else if(ref==1)
		{
			fprintf(fil, "$| %s\n", params);
		}
		else
		{
			fprintf(fil, "$%d| %s\n", ref, params);
		}
		fprintf(fil, ">>>\n");
		fprintf(fil, "%s\n", output);
		fprintf(fil, "<<<\n");
	}
}
