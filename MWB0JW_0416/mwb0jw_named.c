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

	// fifo l�trehoz�sa a f�jlrendszerben
        ret = mkfifo("mwb0jw", 00666);	        
	if (ret == -1) {
	    perror("mkfifo() hiba!");
	    exit(-1);
	}
	// a l�trehozott fifo megnyit�sa
	fd = open("mwb0jw", O_RDWR);	            
	if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
	}

	strcpy(buf, "A hallgato neve: Hudak Daniel");
	printf("fifoba iras\n%s (%ld byte)\n", buf, strlen(buf));
	// be�r�s
	write(fd, buf, strlen(buf));                
	// kiolvas�s (ret: a sikeres kiolvas�s mennyis�ge)
	ret = read(fd, buf, 32);                    
	printf("fifobol olvasas\n%s (%d byte)\n", buf, ret);

	close(fd);
	// t�rl�s fs-r�l
	unlink("mwb0jw");	                       
}

/*
irok a fifoba: ezt teszem a fifoba:19
read() olvasott 19 byteot
*/

