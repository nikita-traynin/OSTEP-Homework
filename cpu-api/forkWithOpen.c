#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
	char msg[] = "Special message from your old friend.";
	int fd = open("./file-to-open.txt", 0);
	printf("Value of the fd we just opened: %d\n", fd);
	fork();
	printf("Size of msg: %lu", sizeof(msg));
	write(fd, msg, sizeof(msg));
	return 0;
}
