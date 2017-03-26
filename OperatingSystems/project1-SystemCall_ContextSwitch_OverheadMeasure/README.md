#System Calls and Context Switch Measurements
Measuring the overhead/costs of a context switch and system calls.
# Context Switch
The cost of a context switch is measured via a bulk operation of forking child processes and taking an average of the results. 
Using sched_setaffinity to advise the kernal to run the parent process (and any other sub-process) on a particular core. 

The cost of a system call is measured in a similar manner by way of massive system calls and taking an average of the data.
The raw time is collected by means of clock_gettime provided by <time.h> 