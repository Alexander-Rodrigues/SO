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

int list_process(LIST l) {
    int pid, status, n;
    int pd[2];
    pipe(pd);
    if (l == NULL) return -1;
    for (int i = 0; i < list_size(l); i++) {
        THING t = list_get_thing(l,i);
        pid = fork();
        if (pid < 0) {
            perror("Error forking");
            return pid;
        }
        if (pid == 0) {
            dup2(pd[0],0);
            dup2(pd[1],1);
            if (i - thing_get_ref(t) > 0) {
                char * buf = thing_get_output(t);
                write(pd[1],buf,strlen(buf));
                
            }
        }
        wait(&status);
        if (WIFEXITED(status)) {
            printf("[%d] SUCCESS >>> %s\n", pid, thing_get_params(t));
        }

    }
}
