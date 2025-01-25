#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
	char msg[100];
	sprintf(msg, "Special message from your old friend, who has pid: %d\n", getpid());
	int fd = open("./file-to-open.txt", O_WRONLY);
	printf("Value of the fd we just opened: %d\n", fd);
	fork();
	printf("Size of msg: %lu\n", sizeof(msg));
	write(fd, msg, sizeof(msg));
	return 0;
}
