#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pipefd[2];
	pipe(pipefd);
	printf("In parent process! Read/write fds of pipe: %d, %d (pid: %d)\n", pipefd[0], pipefd[1], getpid());
	int childPid = fork();
	if(childPid == 0) {
		int childPid2 = fork();
		if (childPid2 == 0) {
			printf("In child 2! (pid: %d)\n", getpid());
			close(pipefd[1]);
			int readEnd = pipefd[0];
			char result[100];
			int count = 0;
			int c;
			while ((c = read(readEnd, result + sizeof(char)*count, sizeof(char))) > 0)
				count += 1;
			printf("Message I received: %s\n", result);
		} else {
			printf("In child 1! (pid: %d)\n", getpid());
			close(pipefd[0]);
			int writeEnd = pipefd[1];
			char msg[] = "\nSpecial message from child 1 to child 2.\n";
			write(writeEnd, msg, sizeof(msg));
			close(writeEnd);
			printf("Waiting on child termination! (pid: %d)\n", getpid());
			wait(NULL);
			printf("A child has terminated. (pid: %d)\n", getpid());
		}
	}else {
		close(pipefd[0]);
		close(pipefd[1]);
		printf("Waiting on child termination! (pid: %d)\n", getpid());
		wait(NULL);
		printf("A child has terminated. (pid: %d)\n", getpid());
	}
	printf("I am exiting now! (pid: %d)\n", getpid());
	return 0;
}
