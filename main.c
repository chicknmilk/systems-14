#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

#include <signal.h>
#include <string.h>

// static means that it circumnavigates the normal call stack
// static variables/functions cannot be accessed from outside the file
static void sighandler(int sig) {

    // handle ctrl c
    if (sig == SIGINT) {
        int f_out = open("exit.data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        char * exit_msg = "program exited due to SIGNINT";
        write(f_out, exit_msg, strlen(exit_msg));
        exit(0); // this thing stops it from running forever
    }
    else if (sig == 30) {
        printf("ppid: %d\n", getppid());
    }
}


int main() {
    signal(SIGINT, sighandler);
    signal(30, sighandler);
    
    while (1) {
        printf("pid: %d\n", getpid());
        sleep(1);
    }
}