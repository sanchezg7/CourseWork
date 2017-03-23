README
To run the program: ./memsim <tracefile> <nFrames> <vms|lru|clk|opt> <debug|quiet>

example: ./memsim gcc.trace 512 lru quiet

expected output:
total memory frames: 256
events in trace: 1000000
total disk reads: 25307
total disk writes: 103