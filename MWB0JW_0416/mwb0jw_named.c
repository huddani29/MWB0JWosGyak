#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd, ret;
	char buf[32];

	buf[0] = 0;

	// fifo létrehozása a fájlrendszerben
        ret = mkfifo("mwb0jw", 00666);	        
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
	// a létrehozott fifo megnyitása
	fd = open("mwb0jw", O_RDWR);	            
	if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
	}

	strcpy(buf, "A hallgato neve: Hudak Daniel");
	printf("fifoba iras\n%s (%ld byte)\n", buf, strlen(buf));
	// beírás
	write(fd, buf, strlen(buf));                
	// kiolvasás (ret: a sikeres kiolvasás mennyisége)
	ret = read(fd, buf, 32);                    
	printf("fifobol olvasas\n%s (%d byte)\n", buf, ret);

	close(fd);
	// törlés fs-rõl
	unlink("mwb0jw");	                       
}

/*
irok a fifoba: ezt teszem a fifoba:19
read() olvasott 19 byteot
*/

