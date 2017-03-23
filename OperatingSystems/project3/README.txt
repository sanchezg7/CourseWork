Name: Gerardo Sanchez
Net Id: sanchezg

Included source files:
cube.h
cube.c
wizard.h
wizard.c
makefile

To compile, extract all source files (including makefile) and type 'make'
run the program with correct flags/specifiers

./cube -size 4 -seed 3 -teamA 2 -teamB 5

In this case there will be (3) + (5) = 8 threads running in parallel, including the main thread of execution (cube)
The program will wait for a specific SEQUENCE of inputs.

To start the game --> 					'start'
To single-step --> 						's'
To continue to the end of the game --> 	'c'
To show the cube -->					'show'
To exit --> 							'exit'




*********************NOTICE********************************************
The code only prints desired debugging statements
In development, many printf statements were used; unnecessary printf have simply been commented out -- NOT DELETED
These surpressed printf statements will help me in the future for reference
Please consult me if there are any questions with control flow, I tried to provide as many comments as deemed necessary to follow.

Thank you for your consideration.
***********************************************************************