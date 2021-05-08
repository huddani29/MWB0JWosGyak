#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd, ret;
    char buf[32];
    char prev[32];

    buf[0] = 0;
    // fifo létrehozása a fájlrendszerben
    ret = mkfifo("mwb0jw", 00666);	            
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
    
    
    fd=open("mwb0jw", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }
    while (fd != -1) {
        // kiolvasás ( ret: kiolvasott mennyiség)
        ret = read(fd, buf, 32);
        if (strcmp(prev, buf) != 0) {
            strcpy(prev, buf);
            printf("A kiolvasott ertek: %s\n", buf);
        }
    }
    close(fd);
    // file törlése az fs-rõl
    unlink("mwb0jw");
    return 0;
}
