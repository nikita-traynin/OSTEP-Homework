#include <stdio.h>
#include <unistd.h>

int main() {
	int childPid = fork();
	if (childPid == 0) {
		int childPid2 = fork();
		if (childPid2 == 0) {
			int childPid3 = fork();
			if(childPid3 == 0) {
				int childPid4 = fork();
			}else {
				char *argArray[] = {"-l", "-a", "."};
				execvp("ls", argArray);
			}
		}
		else {
			execl("/bin/ls", ".", (char*)NULL);
		}
	}else {
		execlp("ls", ".", (char*)NULL);
	}
	return 0;
}
