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

int list_process(LIST l) {
    int pid, status;
    int fd = open("tmp",O_RDWR);

    int pd[2];
    pipe(pd);
    pid = fork();
    if (pid == 0) {
        dup2(fd,0);
        char buf[20];
        int n = read(fd,buf,20);
        write(1,buf,n);
    }
    wait(NULL);
    return 0;
}

int list_process2(LIST l) {
    int pid, status, n;
    int pd[2];
    pipe(pd);
    int fd;
    remove("tmp");
    if (l == NULL) return -1;
    for (int i = 0; i < list_size(l); i++) {
        THING t = list_get_thing(l,i);
        fd = open("tmp",O_CREAT|O_RDWR|O_TRUNC|O_EXCL);
        if (fd < 0) {
            perror("Error creating tmp file");
            return fd;
        }
        write(fd,"1",1);
        pid = fork();

        if (pid < 0) {
            perror("Error forking");
            return pid;
        }
        if (pid == 0) {
            dup2(pd[1],1);
            dup2(fd,0);
            close(pd[0]);
            char * buf = thing_get_params(t);
            execl("/bin/sh", "sh", "-c", buf, (char *) 0);
        }
        else {
            wait(&status);
            if (WIFEXITED(status)) {
                printf("[%d|%d] SUCCESS >>> %s",pid,WEXITSTATUS(status), thing_get_params(t));
                char buff[1024];
                n = read(pd[0],buff,1024);
                buff[n] = '\0';
                printf("\n<<<\n%s>>>\n",buff);
                list_set_thing_output(l,i,buff);
            }
            else {
                perror("error");
                return -1;
            }
        }
        remove("tmp");
    }
    close(pd[1]);
    close(pd[0]);
    return 0;
}
