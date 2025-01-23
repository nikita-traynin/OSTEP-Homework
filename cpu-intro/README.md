# Simulator 

This simulates a simplified process scheduler. 

For cpu-only programs (with no io), it just runs a program until completion, followed by the next program, chosen by lowest pid. In this example the pid is just the index of the process within the process list supplied to the script.

The simulator allows you to choose when context switches happen. By default it's only when a process ends, the alternative is SWITCH_ON_IO (self-explanatory).

An illustrative run is the example: **python3 -m process-run -l 10:80,10:80,10:20,10:10,10:80 -S SWITCH_ON_IO -L 5 -c -p**

It runs 5 processes, 3 of which are more CPU heavy (80%), and two that are i/o-heavy (10% and 20% cpu). It highlights the advantage of switching to another process when one is blocked and waiting for i/o - it allows for overlap and thus better useage of the CPU (AKA **parallelism**). 
# HW Questions

1. Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be ?
   A: 100%. The CPU will always be executing commands since no I/O is requested, and no process will ever be blocked.
2. Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes?
   A: Since the cpu-bound process runs first, it will run to completion. Then, the I/O bound process will run and block until I/O completion. There is no parallelism effectively at play. The CPU usage is at 55%. 
3. Switch the order of the processes: -l 1:0,4:100. What happens now?
   A: Now, the I/O-bound process runs first. It will block after the first instruction, allowing the scheduler to run another process instead. So the 2nd process can run to completion while the 1st one blocks, now our CPU useage is at 86%. There is still one time slice when it's idle, because the second process has already completed but the first still hasn't received an I/O signal.
4. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?
   A: The scheduler will no longer deschedule a process when it issues I/O, so every process will run to completion sequentially.
5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO).
   A: SWITCH_ON_IO is the default behavior, this is the same result as q#3.
6. One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I IO RUN LATER) Are system resources being effectively utilized?
   A: System resources are not being used effectively. The I/O bound process sets in READY state while the other CPU-bound processes wait, instead of first issuing I/O and blocking while they run. This is why I/O-heavy processes should have higher CPU priority. MLFQ takes advantage of this by promoting processes that block for I/O in a time slice to a higher priority queue.
7. Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ?
   A: This is a rudimentary way to maximize cpu useage. On a cpu that is running both I/O-bound and CPU-bound processes, this is much more efficient than RUN_LATER.
8. This last question is just about messing around with some random-ish inputs. I'll leave it blank as I've explained a good bit already :)
