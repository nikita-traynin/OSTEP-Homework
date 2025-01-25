
# Overview

There are now two simulators related to this chapter. The first,
`fork.py`, is a simple tool to show what a process tree looks like
when processes are created and destroyed. Read more about it
[here](README-fork.md).

The second is a program, `generator.py`, that creates real C programs
that use `fork()`, `wait()`, and `exit()` to show how `fork` works in
running programs. Read more about it [here](README-generator.md).

# HW Question (code)
1. Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?  
   A: File: forking.c. The variable is part of the program's memory, so is duplicated upon fork. Both child and parent have the same value for x. Once they change it though, they are stuck with their own versions. One process, of course, cannot access or modify the memory of another process.
2. Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?  
   A: Files: forkWithOpen.c. Both can access the file descriptor. In my example, the process's messages were appended in entirety without breaking. However, I'm not sure whether a context switch could interrupt in the middle of a write() call and clobber the strings being written.  
3. Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?  
   A: Files: forkHelloGoodbye.c. I was able to do this by calling by adding sleep(10) in the parent process and not in the child process.  
4. Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(). Why do you think there are so many variants of the same basic call?  
   A: Files: forkAndExec.c. The variadic version (letter 'l' in execl) is convenient as we can call it without creating an array. It also strictly controls the number of arguments that are passed. If instead we use a version with 'v', we can pass in an arg array. This allows a dynamic amount of arguments, and also allows a potentially huge arg list that can be generated on the fly. The other versions (names with letters 'e' and 'p') allow us to use a custom environment instead of passing the current one, and optionally use the PATH variable to determine the path of the program we want to use.  
5. Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?  
   A: Files: forkAndWait.c. When I accidentally used wait in the child process, I noticed it returned a -1 (signifying an error). This makes sense as the newly forked child does not have any children of its own. However, when used properly in the parent, it returns the PID of the child. It enables the parent to wait for the child to complete. Although sleep(10) did the job, it does not ensure completion. In the case of a slow set of instructions, if they don't complete in 10 seconds, they may be interrupted.  
6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?  
   A: Skipped the coding. Waitpid is a simple idea: by specifying a pid, we can be selective about which child we wait on. Useful if the process spawns multiple children for different purposes.  
7. Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?  
   A: Any further output to STDOUT (which includes printf calls) are not seen anywhere. This is expected when closing a file descriptor.  
8. 

# HW Questions (Simulator)
1. Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step?  
   A: In this simple example, yes. Only leaf processes ever exited, and forking is a deterministic procedure on a process tree.
2. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes?  
   A: This was a more interesting run as we begin to see non-leaf processes exit before their children. In this example, the children (now orphan processes) were all re-parented directly to a (the root process). So sometimes, process that are related as parent-child, can become sibling processes if the parent of the parent is exited first. And as the forking percentage approached 1, the process tree obviously grew much larger and complex.
3. Now, switch the output by using the -t flag (e.g., run ./fork.py -t). Given a set of process trees, can you tell which actions were taken?  
   A: Yes. This is easy because each step either adds a new process or removes one. So we can just see which process went missing or which process is new.
4. One interesting thing to note is what happens when a child exits;what happens to its children in the process tree? To study this, let’s create a specific example: ./fork.py -A a+b,b+c,c+d,c+e,c-.This example has process ’a’ create ’b’, which in turn creates ’c’,which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.  
   A: It looks like, with the -R flag, orphaned process are instead attached to the dead process's parent. This is similar to the removal of a node from a linked list - the list stays intact.
5. One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.  
   A: This one is simple again because the actions are deterministic on the tree. As long as we know what to do with orphaned processes, we're good.  
6. Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.  
   A: We certainly cannot tell the order in which processes forked - that's for sure. But what's more is we also can't tell what actions took place, even out of order. That's because any number of processes in the tree could be former orphans, and we don't know what their parent processes were. The probablistic nature of whether we fork or exit at any step also contributes to this.   
 










