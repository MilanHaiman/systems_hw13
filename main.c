#include <stdio.h>
#include <stdlib.h>
// #include <dirent.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


static void sighandler(int signo) {
	if (signo == SIGINT) {
		int fd = open("logs.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
		char * output = "Exit due to SIGINT\n";
		// strcat(output,ctime(time(NULL)));
		// strcat(output,".\n");
		write(fd, output, strlen(output));
		close(fd);
		exit(0);
	}
	if (signo == SIGUSR1) {
		printf("Parent PID: %d\n", getppid());
	}
}

int main(int argc, char const *argv[]) {

	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while(1) {
		printf("PID: %d\n", getpid());
		sleep(1);
	}
	return 0;
}