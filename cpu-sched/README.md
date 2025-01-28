# Homework (Simulator)
1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.  
  Simple command run. `./scheduler.py --jlist=200,200,200 --policy=FIFO`, `./scheduler.py --jlist=200,200,200 --policy=SJF`. Notice that SJF and FIFO perform the same here. This is because all the jobs have the same length.
2. Now do the same but with jobs of different lengths: 100, 200, and 300.
   Simple command run. `./scheduler.py --jlist=100,200,300 --policy={FIFO|SJF}`. The results here are still the same as the previous one. That is because the jobs are given in order of shortest to longest length, so FIFO and SJF will run in the same order. 
3. Now do the same, but also with the RR scheduler and a time-slice of 1.
   Simple command run. `./scheduler.py --jlist=100,200,300 --policy=RR --quantum=1`
4. For what types of workloads does SJF deliver the same turnaround times as FIFO?
   A: For a job list ranked in order of job length, FIFO and SJF yield the same result. The order inputted doesn't matter for SJF as it will sort the jobs by length. A poorly ordered job list for FIFO will result in all but one job being completely blocked waiting for the first job to executed. If one of the first few jobs is very long, this is a poor user experience.
5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
   A: If the length of jobs is equal to or below the quantum, and the job list order is from shortest to longest, then SJF and RR have the same result. Typically, RR provides a much shorter response time than SJF. The longest possible response time for RR is (n-1)*quantum, where n is the number of jobs. For SJF it's length(job0) + length(job1) + ... + length(jobn-1).
6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?
   A: Response time degrades linearly with respect to job length. Run the following command: `./scheduler.py --policy=RR --quantum=1 --jlist=a,a,a,a` with `a` varying from 1 to 25.
7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
   A: The longest possible response time for RR is (n-1)*quantum. As you can see, it increases linearly with quantum. Best-case is always 0, average case also increases linearly with quantum. 
