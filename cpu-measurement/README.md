# Measurement
Files: measurePipe.c

The first task was simply to create a pipe where one child writes to another.
I had already done this, but I wanted to upgrade it by writing an arbitrary number of bytes to the pipe, and reading exactly how much was written and not any more or less. 
The main obstacles I ran into while trying to do that: 
1. After forking the two children, I was accidentally letting the parent exit first. This result in bash displaying a new prompt followed by output from the two children, which looks messy. I fixed this by adding a wait in the parent. 
2. The read() call in Linux will actually block until it receives an input. This was causing my program to hang.
3. EOF will only be reached in a read side of the pipe once the write end of the pipe is closed.
4. I attempted to fix the issue in #3 by calling close() in the child immediately after the write() call, but this did not work either. Then I realized that the parent process, which is where I first created the pipe before any forking, still has this fd. Turns out, I needed to call close() on all processes that had an fd for the write end of this pipe.

Notice that I actually had child 1 fork into child 2. So the two children process are not siblings on the same level in the process tree, though it could be done like that as well.

The next step was setting up two pipes in each direction, and timing the reads.
Files: measurePipe2.c

