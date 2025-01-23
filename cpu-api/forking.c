#include <stdio.h>
#include <unistd.h>

int main() {
	int x = 5;
	printf("Hello World!\n");
	fork();
	printf("Value of x: %d (pid: %d)\n", x, getpid());
	return 0;
}
