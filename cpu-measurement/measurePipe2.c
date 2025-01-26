#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sched.h>

int main() {
	printf("Initiating parent process! (pid: %d)\n", getpid());
	int childPid = fork();
	if (childPid == 0) {
		printf("Initiating child process 1! (pid: %d)\n", getpid());
		int pipefd[2];
		int pipefd2[2];
		pipe(pipefd);
		pipe(pipefd2);
		int childPid2 = fork();
		if (childPid2 == 0) {
			cpu_set_t set;
			CPU_SET(0, &set);
			sched_setaffinity(getpid(), sizeof(set), &set);
			printf("Initiating child process 2! (pid: %d)\n", getpid());
			close(pipefd[1]);
			int read1 = pipefd[0];
			close(pipefd2[0]);
			int write2 = pipefd2[1];

			
			char msg[2000];
			long long int times[2000];
			int count = 0;
			struct timeval c1, c2;
			while (count < 2000) {
				gettimeofday(&c1, NULL);
				read(read1, msg + count*sizeof(char), sizeof(char));
				gettimeofday(&c2, NULL);
				write(write2, "a", sizeof(char));
				times[count] = (c2.tv_sec - c1.tv_sec)*1000000LL + c2.tv_usec - c1.tv_usec;
				printf("Count: %d, timing: %lld, pid: %d\n", count, times[count], getpid());
				count += 1;
			}
			close(write2);
			close(read1);
			double sum = 0;
			for(int i = 0; i < 1999; i++) {
				sum += times[i];
			}
			printf("Average time to read from fd as calculated from pid %d: %fms\n", getpid(), sum / (1999*1000));
		} else {
			cpu_set_t set;
			CPU_SET(0, &set);
			sched_setaffinity(getpid(), sizeof(set), &set);
			close(pipefd[0]);
			int write1 = pipefd[1];
			close(pipefd2[1]);
			int read2 = pipefd2[0];

			char msg[2000];
			long long int times[2000];
			int count = 0;
			struct timeval c1, c2;
			while(count < 2000) {
				write(write1, "a" ,sizeof(char));
				gettimeofday(&c1, NULL);
				read(read2, msg + count*sizeof(char), sizeof(char));
				gettimeofday(&c2, NULL);
				times[count] = (c2.tv_sec - c1.tv_sec)*1000000LL + c2.tv_usec - c1.tv_usec;
				printf("Count: %d, timing: %lld, pid: %d\n", count, times[count], getpid());
				count +=1;
			}
			close(write1);
			close(read2);
			double sum = 0;
			for(int i = 0; i < 1999; i++) {
				sum += times[i];
			}
			printf("Average time to read from fd, as calculated from pid %d: %fms\n", getpid(), sum / (1999*1000));
			wait(NULL);
		}
	} else {
		wait(NULL);
	}
	return 0;
}
