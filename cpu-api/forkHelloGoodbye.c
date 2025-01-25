#include <stdio.h>
#include <unistd.h>

int main() {
	int ppid = fork();
	if (ppid == 0) {
		printf("Hello from child! (pid: %d)\n", getpid());
	} else {
		sleep(10);
		printf("Hello from parent! (pid: %d)\n", getpid());
	}
	return 0;
}
