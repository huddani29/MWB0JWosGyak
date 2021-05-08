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
    int fd, ret;
    char buf[32];
    
    buf[0] = 0;

    
    fd=open("mwb0jw", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }

    strcpy(buf, "A hallgato neve: Hudak Daniel");
	printf("fifoba iras\n%s (%ld byte)\n", buf, strlen(buf));
	write(fd, buf, strlen(buf));

    close(fd);
    
    return 0;
}
