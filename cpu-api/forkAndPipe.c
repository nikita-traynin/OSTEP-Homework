#include <stdio.h>
#include <unistd.h>

int main() {
	int pipefd[2];
	pipe(pipefd);
	int childPid = fork();
	if (childPid == 0) {
		printf("In child 1! (pid: %d)\n", getpid());
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);	
		printf("This is a secret message from child 1\n");
	}else {
		int childPid2 = fork();
		if (childPid2 == 0) {
			printf("In child 2! (pid: %d)\n", getpid());
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			char msg[100];
			fgets(msg, sizeof(msg), stdin);
			printf("Message I received as pid %d: %s\n", getpid(), msg);
		}
	}
	return 0;
}
