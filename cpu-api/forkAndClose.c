#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Printing something in parent, pre-fork (pid: %d)\n", getpid());
	int childPid = fork();
	if (childPid == 0) {
		printf("Printing in child, before closing stdout. (pid: %d)\n", getpid());
		close(STDOUT_FILENO);
		printf("Printing in child after closing stdout (pid: %d)\n", getpid());
	} else {
		printf("Printing in parent post-fork! (pid: %d)\n", getpid());
	}
	return 0;
}
