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
    
    buf[0] = 0;
    // fifo létrehozása a fájlrendszerben
    ret = mkfifo("mwb0jw", 0777);	            
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
    
    
    fd=open("mwb0jw", O_RDWR);
    if (fd==-1){
        perror("mkfifo() hiba!");
	    exit(-1);    
    }
    // kiolvasás ( ret: kiolvasott mennyiség)
    ret = read(fd, buf, 32);                    
	printf("kiolvasás\n%s (%d byte)\n", buf, ret);
    close(fd);
    // file törlése az fs-rõl
	unlink("mwb0jw");	                       
    
    return 0;
}
