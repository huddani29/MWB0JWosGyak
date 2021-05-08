#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    // két változó a cső két végének ---> két elemű tömb
    int pipefd[2];   
    // gyerek pidje
    pid_t cpid; 
    // buffer
    char buf;       
    // a küldendő szöveg bufferje
    char kuldendo[32];            
    int ret;

    // csővezeték létrehozása, az fd-ket a pipefd-ben tároljuk
    if (pipe(pipefd) == -1) {	
	    perror("pipe");
	    exit(-1);
    }

    /* printf("%d: fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]); */

    cpid = fork();
    if (cpid == -1) {
	    perror("fork");
	    exit(-1);
    }

    if (cpid == 0) {            /* gyerek vagyok */
        /*printf("%d: gyerek vagyok\n", getpid());*/     //ez a cső most nem kell
        //a gyerek csak ír, azonnali bezárás
	    close(pipefd[0]);	    //olvasóvég becsuk


        printf("%d: gyerek vagyok\n", getpid());
        // buffer feltöltése a küldendő stringgel
        strcpy(kuldendo, "HD mwb0jw");                    
        printf("%d: szoveg kuldes: %s (%ld db. karakter)\n", getpid(), kuldendo, strlen(kuldendo));
        // csőbe írás
        write(pipefd[1], kuldendo, strlen(kuldendo));	    

        close(pipefd[1]);       // a gyerek befejezte az irast ---> írás fd lecsukása
        exit(0);	                                    // kilépés
    }

    else {	                    /* szulo vagyok */
        printf("%d: szulo vagyok\n", getpid());
        close(pipefd[1]);       // csatorna küldő végének lezárása ---> masik oldalon EOF

        // várakozás a gyerekre
        wait(NULL);             
        printf("%d: cso ellenorzese\n%d: ", getpid(), getpid());
        // a cső kimenetének olvasása 1 byte-onként, amíg van adatfolyam
   	    while (read(pipefd[0], &buf, 1) > 0) {	  
            printf("%c", buf);
	    }
        printf("\n");
        // olvasó végének lezárása
        close(pipefd[0]);       
        // várakozás a gyerekre
	    wait(NULL);             
        exit(0);
    }
}

/* Eredmény formája:

5611: fd1: 3, fd2: 4
5611: szulo vagyok
5611: szovegkuldes: szoveg (23 db. karakter)
5612: gyerek vagyok
5612: cso ellenorzese
5612: szoveg

*/
