#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int childPid = fork();
	if (childPid == 0) {
		printf("In the child! (pid: %d)\n", getpid());
	} else {
		int childStatus;
		pid_t wait_result = wait(&childStatus);
		printf("In the parent! (pid: %d)\n", getpid());
		printf("Result from wait: %d\n", wait_result);
		if (wait_result == -1) {
			if (WIFEXITED(childStatus)) {
				printf("The child exited normally!\n");
			} else {
				printf("The child did not exit normally!\n");
			}
		}	
	}
	return 0;
}
