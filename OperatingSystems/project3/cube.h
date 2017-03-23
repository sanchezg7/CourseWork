#ifndef _CUBE_H
#define _CUBE_H

#include <semaphore.h>

#define SOLUTION

struct cube;

sem_t wizardMutex;            // only one wizard (THREAD) can go at a time
sem_t intWizMutex;            //wizard taking a turn or the interface
int turnFlag;                 //indicates when a wizards turn is over  //0 - turn is over, 1 - wizard is taking a turn
pthread_t *teamAThreads;      //holds their teamA threads
pthread_t *teamBThreads;      //holds their teamB threads

struct wizard {
  int x; 			          //current grid spot G.S.
  int y;			
  int id; 		
  char team;			      //holds team name
  int status; 			    /* 0: alive, 1: frozen */
  struct cube *cube; 		//the cube it belongs to
  sem_t statusSem;	  	//will freeze/unfreeze the wizard G.S.  
};
  
  
  //2D array format [num_rows][num_columns];
struct room {
  int x;	//gives row
  int y;	//give col
  struct wizard *wizards[2]; //holds only two wizards

	/* 	Fill in as required 	*/
};

struct cube {
  int size;
  int teamA_size;
  int teamB_size;
  struct wizard **teamA_wizards;	//holds the wizards for the game
  struct wizard **teamB_wizards;
  int game_status;			          //indicates if the game has ended, 1=gameOver 0=gameI.P.

  /* Pointer to a two-dimensional array of rooms */
  struct room ***rooms; 		      // rooms --> roomRow --> roomCol, verfiy

  /* Fill in as required */
};

extern void print_wizard(struct wizard *);
extern void kill_wizards(struct cube* cube_ref);
extern void print_cube(struct cube *);
extern int check_winner(struct cube* cube);

extern void dostuff();								//spin
extern struct room * choose_room(struct wizard*);
extern int try_room(struct wizard *, struct room *, struct room* );		//check if the room switch can happen (room non-full)
extern void switch_rooms(struct wizard *, struct room *, struct room* ); 	//actually perform the switch
extern struct wizard * find_opponent(struct wizard*, struct room *);		
extern int fight_wizard(struct wizard *, struct wizard *, struct room *);	//carries out fighting mechanism
extern int free_wizard(struct wizard *, struct wizard *, struct room *);	//carries out unfreezing mechanism

extern int loopSteps(struct cube*cube_ref);
extern int step(struct cube*cube_ref);

#endif
