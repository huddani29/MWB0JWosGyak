#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd, ret, ofs, pid;
    char buf[32];
    
    pid = getpid();
    buf[0] = 0;
    ofs = 0;
    
    fd=open("mwb0jw", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }
    while (fd != -1) {
        sprintf(buf, "%d", pid + ofs);
        printf("A beirt ertek: %s \n", buf);
        write(fd, buf, strlen(buf));
        ofs += 2;
        sleep(1);
    }
    close(fd);
    
    return 0;
}
