#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int stat, pid, ppid, gpid;

int main(int argc, char* argv[], char* env[]) {
	// Parent PID-jének röggzítése
	ppid = getpid();
	// Child process
	if ((pid = fork()) == 0) {
		printf("\n Child pid = %d \n", getpid());
		stat = execl("./child", "ls", "-l", (char*)NULL);
		if (stat == -1) {
			perror("parent execl failed");
			exit(0);
		}
	}
	// Parent process
	printf("\n %d.sz. Parent var a %d.sz. child process-e.\n ", ppid, pid);
	if (pid != wait(&stat)) perror(" Parent - varakozas hiba ");
	return 0;
}