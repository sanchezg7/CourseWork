# Page Replacement Algorithm performance
Reports the performance of page replacement algorithms given different conditions. Such conditions are:
- Total # of frames available
- Total # of events in a trace
- Total disk reads
- Total disk writes

Example trace:
0041f7a0 R
13f5e2c0 R
05e78900 R
004758a0 R
31348900 W

# Algorithms
- VMS
- LRU
- CLK
- OPT

# Invoke 
memsim <tracefile> <nframes> <vms|lru|clk|opt>