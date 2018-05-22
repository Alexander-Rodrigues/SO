/** @file */

#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dataStructs.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * Processes l, fillin all output fields
 * @param  l a LIST
 * @return   and int indicating how the process went
 * /note hello
 */
int list_process(LIST list) {
    int pid, status, n;
    int pd[2];
    pipe(pd);
    int fd;
    char buf[1024];
    fd = open("tmp",O_WRONLY|O_CREAT|O_TRUNC,S_IRWXO|S_IRWXU);
    write(fd,"12345",5);

    for (int i = 0; i < list_size(list); i++) {
        THING t = list_get_thing(list,i);
        fd = open("tmp",O_WRONLY|O_TRUNC);
        if (thing_get_ref(t) > 0) {
            THING t2 = list_get_thing(list,i - thing_get_ref(t));
            char *output = thing_get_output(t2);
            write(fd, output,strlen(output));
        }
        pid = fork();
        if (pid == 0) {
            close(fd);
            fd = open("tmp",O_RDONLY);
            dup2(fd,0);
            dup2(pd[1],1);
            close(pd[1]);
            close(pd[0]);

            execl("/bin/sh", "sh", "-c",thing_get_params(t), (char *) 0);
        }
        wait(NULL);
        n = read(pd[0],buf,1024);
        close(fd);
        char *c = malloc(n);
        c = strncpy(c,buf,n);
        c[n] = '\0';
        list_set_thing_output(list,i,c);
    }
    remove("tmp");
    return 0;
}
