#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cube.h"
#include "wizard.h"

#define DEFAULT_CUBE_SIZE 4
#define DEFAULT_TEAM_SIZE 5
#define DEFAULT_SEED 1
#define HOWBUSY 100000000
#define TRUE 1
#define FALSE 0

void 
command_line_usage()
{
  fprintf(stderr, "-size <size of cube> -teamA <size of team> -teamB <size of team> -seed <seed value>\n"); 
}

void 
kill_wizards(struct cube* cube_ref)
{
  int teamA_size = cube_ref->teamA_size;
  int teamB_size = cube_ref->teamB_size;
  int i;

  //kill all teamA threads (Wizards) 
  for(i = 0; i < teamA_size; ++i)
  {
    //printf("Send cancel request to teamA thread %d\n", i);
    assert(pthread_cancel(teamAThreads[i]) == 0);
  }

  for(i = 0; i < teamB_size; ++i)
  {
    //printf("Send cancel request to teamB thread %d\n", i);
    assert(pthread_cancel(teamBThreads[i]) == 0);
  }

  


  return;
}

int 
check_winner(struct cube* cube)
{
  /* Fill in */
  int i;
  int teamA_size = cube->teamA_size;
  int teamB_size = cube->teamB_size;

  for (i = 0; i < teamA_size; ++i)
  {
    if(cube->teamA_wizards[i]->status == 1)
    {
      //continue
      //printf("Wizard %c%d is frozen. Status: %d\n", cube->teamA_wizards[i]->team, cube->teamA_wizards[i]->id, cube->teamA_wizards[i]->status);
    }
    else {
        break;
    }
    if(i == (teamA_size-1))
    {
      printf("Team B won the game!\n");
      return 2; //all of teamA is frozen, teamB won
    }
  }

  for(i = 0; i < teamB_size; ++i)
  {
    if(cube->teamB_wizards[i]->status == 1)
    {
      //continue
      //printf("Wizard %c%d is frozen. Status: %d\n", cube->teamB_wizards[i]->team, cube->teamB_wizards[i]->id, cube->teamB_wizards[i]->status);
    }
    else {
        break;
    }
    if( i == (teamB_size-1))
    {
      printf("Team A won game!\n");
      return 1; //all of teamB is frozen, teamA won
    }

  }

  //eventually game_status needs to equal 1 to indicate FINISHED

  //printf("No winner yet.\n");
  return 0; //game status is still running
}

void 
print_cube(struct cube *cube)
{
  int i;
  int j;
  int k;

  assert(cube);

  for (i = 0; i < cube->size; i++)
  {
      printf("+");
      for (j = 0; j < cube->size; j++)
	    {
	      printf("--+");
	    }
      printf("\n|");
      
      for (j = 0; j < cube->size; j++)
	    {
	      /* Print the status of wizards in this room here */
	      for (k = 0; k < 2; k++)
	        {
	          if (cube->rooms[j][i]->wizards[k] != NULL)
		    {
		      if (cube->rooms[j][i]->wizards[k]->status)
		        {
		          printf("%c", tolower(cube->rooms[j][i]->wizards[k]->team)); //print lowercase -- FROZEN (Status was 1)
		        }
		      else
		        {
		          printf("%c", toupper(cube->rooms[j][i]->wizards[k]->team)); //print uppercase -- ACTIVE (Status was 0)
		        }
		    }
	          else 
		    {
		      printf(" ");
		    }
	        }
	      printf("|");
	    }
      printf("\n");
  }
  printf("+");
  for (j = 0; j < cube->size; j++)
  {
    printf("--+");
  }
  printf("\n");
  return;
}

/*
	will return an initialized wizard that belongs to a CUBE, team, and has a certain ID
*/
struct wizard *init_wizard(struct cube* cube, char team, int id)
{
  int x, newx;
  int y, newy;
  int initflag;
  struct wizard *w;

  w = (struct wizard *)malloc(sizeof(struct wizard)); //allocate for new wizard
  assert(w);

  initflag = FALSE;
  
  w->team = team; //passed in
  w->id = id;  	  //passed in
  w->status = 0;  //alive
  w->cube = cube; //associate a cube with it
  

  /* Place this NEW wizard in a room in the cube */
  //randon function to determine where to place in the grid/cube
  x = rand() % cube->size; 
  y = rand() % cube->size;
  

  //associate the WIZARD with the CUBE
  if (cube->rooms[x][y]->wizards[0] == NULL) //check if there is a wizard in spot one
  {
    cube->rooms[x][y]->wizards[0] = w;
    w->x = x;
    w->y = y;
  }
  else if (cube->rooms[x][y]->wizards[1] == NULL) //check if these is a wizard in spot two
  {
    cube->rooms[x][y]->wizards[1] = w;
    w->x = x;
    w->y = y;
  }
  else //both spots in this room are occupied by wizards -- PLACE IN ANOTHER ROOM
  {
    newx = (x + 1) % cube->size;
    if (newx == 0) newy = (y + 1) % cube->size;
    else newy = y;

    while((newx != x || newy != y) && !initflag)
    {

      if (cube->rooms[newx][newy]->wizards[0] == NULL) //spot 0 is empty, place wizard here
        {
          cube->rooms[newx][newy]->wizards[0] = w; //assign wizard to room
          w->x = newx;
          w->y = newy;
          initflag = TRUE;
        }
      else if (cube->rooms[newx][newy]->wizards[1] == NULL) //spot 1 is empty, place wizard here
        {
          cube->rooms[newx][newy]->wizards[1] = w; //assign wizard to room
          w->x = newx;
          w->y = newy;
          initflag = TRUE;
        }
      else //no empty space in the current room, place into another ROOM by incrementing x; then y to jump to a new row when x is 0
      {
        newx = (newx + 1) % cube->size; 
        
        if (newx == 0)
        {
          newy = (newy + 1) % cube->size;
        }
      }
      
   }

    if (!initflag){
      free(w);
      return NULL;
    }
  }

  /* Fill in */
  //make(initialize) the statusSemaphore 1
  sem_init(&(w->statusSem), 0, 1); //Wizard initialized to ACTIVE


  return w; //return the Wizard struct
}

int
loopSteps(struct cube* cube_ref)
{
  //0 - turn is over, 1 - wizard is taking a turn
  //printf("In loopSteps. game_status: %d.\n", cube_ref->game_status);

  while(cube_ref->game_status < 1) //while game is still running
  {
    if(!turnFlag) //its nobodies turn (0)
    {
      //printf("It's nobodies turn, giving wizard a turn\n");
      turnFlag = 1;      
      step(cube_ref);
      
    }
  }
  
  if(cube_ref->game_status >= 1)
  {
    //printf("Game over. game_status: %d\n", cube_ref->game_status);
    //kill all the wizard threads
    kill_wizards(cube_ref);
    return cube_ref->game_status;
  }
  else {
    printf("Shouldn't be here!");
    exit(-1);
  }
}

//wizard must reliquish turn (sem_wait(&wizardMutex)) after he is done

int
step(struct cube* cube_ref) //allow a wizard to take a single turn here
{


  //printf("cube->game_status: %d\n", cube_ref->game_status);
  
  //printf("waking a wizard to take a turn.\n");
  sem_post(&wizardMutex); //activate a a wizard to take a turn
  //printf("sleeping interface mutex\n");
  sem_wait(&intWizMutex); //freezes interface until the wizard finishes their turn
  //when awoken, check if there is a winner
  //printf("step function awake. Going to check for a winner.\n");
  cube_ref->game_status = check_winner(cube_ref);
  //print_cube(cube_ref);
  
  return cube_ref->game_status;
}

int 
interface(struct cube*cube_ref)
{
  struct cube* cube;
  char *line;
  char *command;
  int i;
  
  cube = (struct cube *)cube_ref;
  assert(cube);

  using_history();
  while (1)
    {

      line = readline("cube> ");
      if (line == NULL) continue;
      if (strlen(line) == 0) continue;
      
      add_history(line);

      i = 0;
      //sits and waits for actual USER input
      while (isspace(line[i])) i++; //makes system ignore whitespace in the command
      
      command = &line[i];

      //printf("i: %d\n", i);

      if (!strcmp(command, "s"))
      {
        if(cube->game_status == -1)
        {
          fprintf(stderr, "Game has not started, cannot single-step\n");                
        }
        else if (cube->game_status == 0)
        {
  	      step(cube); 
        }
      }
      else if (!strcmp(command, "c"))
      {
	      if(cube->game_status == -1)
		    {
		      fprintf(stderr, "Game has not started, cannot continue\n");                
		    }
        else if (cube->game_status == 0)
        {
	       //printf("'c' presssed, looping until the end.\n");
         loopSteps(cube);
        }
      }      
      else if (!strcmp(command, "exit"))
	    {
	      return 0;
	    }
      else if (!strcmp(command, "show"))
	    {
	      print_cube(cube);
	    }
      else if (!strcmp(command, "start"))
	    {
	      if (cube->game_status >= 1)
	      {
	        fprintf(stderr, "Game is over. Cannot be started again\n");
	      }
	      else if (cube->game_status == 0)
	      {
	        fprintf(stderr, "Game is in progress. Cannot be started again\n");
	      }
	      else
	      {
	        cube->game_status = 0;
	        
	        /* Start the game */

	        /* Fill in */
	      }
	    }
      else if (!strcmp(command, "stop"))
      {
	      /* Stop the game */
	      return 1;
      }
      else
	    {
	      fprintf(stderr, "unknown command %s\n", command);
	    }

      free(line);
    }

  return 0;
}

int 
main(int argc, char** argv)
{
  int cube_size = DEFAULT_CUBE_SIZE;		//4
  int teamA_size = DEFAULT_TEAM_SIZE;		//5
  int teamB_size = DEFAULT_TEAM_SIZE;		//5
  unsigned seed = DEFAULT_SEED;			    //1
  struct cube *cube;				            //cube pointer
  struct room *room;				            //room pointer
  struct room **room_col;			          //columns of rooms
  int res;					                    //result from interface
  struct wizard *wizard_descr;          //temp buffer for a new wizard
  int i, j;
  
  //printf("Init wizardMutex to 0...\n");
  //printf("Init turnFlag to 0\n");
  turnFlag = 0;
  sem_init(&wizardMutex, 0, 0); //initialize wizardMutex to zero
  sem_init(&intWizMutex, 0, 0); //initialized to ZERO

  /* Parse command line and fill:
     teamA_size, timeBsize, cube_size, and seed */

  i = 1;
  while(i < argc) 
  {
    if (!strcmp(argv[i], "-size")) 
    {
    i++;
    if (argv[i] == NULL) 
            {
              fprintf(stderr, "Missing cube size\n");
              command_line_usage();
              exit(-1);
            }
          cube_size = atoi(argv[i]);
    if (cube_size == 0)
      {
              fprintf(stderr, "Illegal cube size\n");
              exit(-1);
      }
    }
    else if (!strcmp(argv[i], "-teamA")) 
    {
      i++;
      if (argv[i] == NULL) 
      {
        fprintf(stderr, "Missing team size\n");
        command_line_usage();
        exit(-1);
      }
      teamA_size = atoi(argv[i]);
      if (teamA_size == 0)
      {
              fprintf(stderr, "Illegal team size\n");
              exit(-1);
      }
    }
    else if (!strcmp(argv[i], "-teamB")) 
    {
      i++;
      if (argv[i] == NULL) 
      {
        fprintf(stderr, "Missing team size\n");
        command_line_usage();
        exit(-1);
      }
      teamB_size = atoi(argv[i]);
      if (teamB_size == 0)
      {
              fprintf(stderr, "Illegal team size\n");
              exit(-1);
      }
    }
    else if (!strcmp(argv[i], "-seed")) 
    {
      i++;
      if (argv[i] == NULL) 
      {
        fprintf(stderr, "Missing seed value\n");
        command_line_usage();
        exit(-1);
      }
      seed = atoi(argv[i]);
      if (seed == 0)
      {
              fprintf(stderr, "Illegal seed value\n");
              exit(-1);
      }
    }
    else
    {
      fprintf(stderr, "Unknown command line parameter %s\n", argv[i]);
      command_line_usage();
      exit(-1);
    }
    i++;
  }

  /* Sets the random seed */
  srand(seed);

  /* Checks that the number of wizards does not violate
     the "max occupancy" constraint */
  if ((teamA_size + teamB_size) > ((cube_size * cube_size) * 2))
  {
    fprintf(stderr, "Sorry but there are too many wizards!\n");
    exit(1);
  }


  //allocate space for ALL threads on each team
  teamAThreads = (pthread_t*) malloc(sizeof(pthread_t) * teamA_size);
  teamBThreads = (pthread_t*) malloc(sizeof(pthread_t) * teamB_size);

  /* Creates the cube */
  cube = (struct cube *)malloc(sizeof(struct cube));
  assert(cube);
  cube->size = cube_size;
  cube->game_status = -1; //game has not yet started

  /* Creates the rooms */
  cube->rooms = malloc(sizeof(struct room **) * cube_size);
  assert(cube->rooms);

  for (i = 0; i < cube_size; i++)
  {
    /* Creates a room column */
    room_col = malloc(sizeof(struct room *) * cube_size);
    assert(room_col);

    for (j = 0; j < cube_size; j++)
    {
      /* Creates a room */
      room = (struct room *)malloc(sizeof(struct room));
      assert(room);
      room->x = i;
      room->y = j;
      room->wizards[0] = NULL;
      room->wizards[1] = NULL;
      room_col[j] = room;

      /* Fill in */
    //What do I fill IN?
    }
    
    cube->rooms[i] = room_col;
  }

  /* Creates the wizards and positions them in the cube */
  cube->teamA_size = teamA_size;
  cube->teamA_wizards = (struct wizard **)malloc(sizeof(struct wizard *) * 	//allocate the space teamA
						 teamA_size);
  assert(cube->teamA_wizards);

  cube->teamB_size = teamB_size;
  cube->teamB_wizards = (struct wizard **)malloc(sizeof(struct wizard *) * //allocate the space for teamB
						 teamB_size);

  assert(cube->teamB_wizards);

  /* Team A */
  for (i = 0; i < teamA_size; i++)
  {
      //wizard_descr is a temp wizard to assign to the cube
      if ((wizard_descr = init_wizard(cube, 'A', i)) == NULL)
      {
        fprintf(stderr, "Wizard initialization failed (Team A number %d)\n", i);
        exit(1);
      }
      cube->teamA_wizards[i] = wizard_descr;
//      printf("Creating thread (Wizard %c%d)\n",wizard_descr->team, wizard_descr->id);
      pthread_create(&(teamAThreads[i]), NULL, (void *) wizard_func, (void *) wizard_descr);
  }

  /* Team B */
  for (i = 0; i < teamB_size; i++)
  {
    if ((wizard_descr = init_wizard(cube, 'B', i)) == NULL)
    {
      fprintf(stderr, "Wizard initialization failed (Team B number %d)\n", i);
      exit(1);
    }
    cube->teamB_wizards[i] = wizard_descr;
//    printf("Creating thread (Wizard %c%d)\n", wizard_descr->team, wizard_descr->id);
    pthread_create( &(teamBThreads[i]), NULL,  (void *) wizard_func, (void *) wizard_descr);
  }  
  /* Fill in */
  
  /* Goes in the interface loop */
  
  res = interface(cube);

  exit(res); //terminate the program
}

void dostuff()
{
  int i;
  int wait;
  
  wait = rand() % HOWBUSY;

  for (i = 0; i < wait; i++) {}

  return;
}

//chooses proper side to side/ up to down movement for room. NO DIAGONGAL MOVEMENT
struct room * 
choose_room(struct wizard* w)
{
  int newx = 0; 
  int newy = 0;

  /* The two values cannot be both 0 - no move - or 1 - diagonal move */ 
  while (newx == newy)
  {
    newx = rand() % 2;
    newy = rand() % 2;
  }
  if ((rand() % 2) == 1) { //WILL THIS RETURN THE SAME VALUE WHEN CALLING RAND AGAIN?
    newx = 0 - newx;
    newy = 0 - newy;

    //printf("In choose_room -- newx %d and newy %d\n", newx, newy);
  }

  return w->cube->rooms[(w->x + w->cube->size + newx) % w->cube->size][(w->y + w->cube->size + newy) % w->cube->size]; 

}


//see if the wizard can move into the newroom
int 
try_room(struct wizard *w, struct room *oldroom, struct room* newroom)
{

  /* Fill in */
  //see if the room is habitable for a wizard, given the new room
  //the room slot 0 must be NULL or the slot 1 must be NULL

  //printf("In try_room... room(%d, %d)", newroom->x, newroom->y);
  //associate the WIZARD with the CUBE
  if (newroom->wizards[0] == NULL) //check for EMPTY slot ONE
  {
    //found space in this room, slot ONE
    //printf("found space in slot ONE!\n");
    return 0;
  }
  else if (newroom->wizards[1] == NULL) //check for EMPTY slot TWO
  {
    //found space in this room, slot TWO
    //printf("found space in slot TWO!\n");
    return 0;
  }

  printf("Request denied, room locked!\n");
  return 1; //indicate FAILURE, could not find room here
  
}

//used to assign the opponent in the same room (OTHER WIZARD)
struct wizard *
find_opponent(struct wizard* self, struct room *room)
{
  struct wizard *other = NULL;

  /* Updates room wizards and determines opponent */
  if ((room->wizards[0] == self))
    {
      other = room->wizards[1];
    }
  else if (room->wizards[1] == self)
    {
      other = room->wizards[0];
    }
  
  return other;
}

//performs action of switching a wizard to a new room
//the check has already been conducted
void 
switch_rooms(struct wizard *w, struct room *oldroom, struct room* newroom)
{
  struct wizard *other;

  /* Removes self from old room */
  if (oldroom->wizards[0] == w)
  {
    oldroom->wizards[0] = NULL;
  }
  else if (oldroom->wizards[1] == w)
  {
    oldroom->wizards[1] = NULL;
  }
  else /* This should never happen */
  {
    printf("Wizard %c%d in room (%d,%d) can't find self!\n",
     w->team, w->id, oldroom->x, oldroom->y);
    print_cube(w->cube);
    exit(1);
  }
  
  //printf("Wizard removed self from the old room.\n");

  /* Fill in */

  /* Updates room wizards and determines opponent */
  if (newroom->wizards[0] == NULL)
  {
    newroom->wizards[0] = w;
    other = newroom->wizards[1]; //why is this here?
  }
  else if (newroom->wizards[1] == NULL)
  {
    newroom->wizards[1] = w;
    other = newroom->wizards[0]; //why is this here?
  }
  else /* This should never happen */
  {
    printf("Wizard %c%d in room (%d,%d) gets in a room already filled with people!\n",
     w->team, w->id, newroom->x, newroom->y);
    print_cube(w->cube);
    exit(1);
  }
  
  /* Sets self's location to current room */
  w->x = newroom->x;
  w->y = newroom->y;

  //printf("Wizard set location in new room.\n");
}

int 
fight_wizard(struct wizard *self, struct wizard *other, struct room *room)
{
  int res;

  /* Computes the result of the fight */
  res = rand() % 2;
		  
  /* The opponent becomes frozen */
  if (res == 0)
  {
    printf("Wizard %c%d in room (%d,%d) freezes enemy %c%d\n",
     self->team, self->id, room->x, room->y,
     other->team, other->id);

    /* Fill in */
    //wizard *other set to status 1 -- FROZEN
    //sem_wait on the other wizard thread, block thread
  }

  /* Self freezes and release the lock */
  else
  {
    printf("Wizard %c%d in room (%d,%d) gets frozen by enemy %c%d\n",
     self->team, self->id, room->x, room->y,
     other->team, other->id);

    /* Fill in */
    //wizard *self gets status 1 -- FROZEN
    //sem_wait on the self wizard thread, block the thread
    

    return 1; //self-freeze code
  }
  return 0; //other freeze code
}


//unfreezes the wizard 
int 
free_wizard(struct wizard *self, struct wizard *other, struct room* room)
{
  int res;	//result

  /* Computes the results of the unfreeze spell */
  res = rand() % 2;	//random function determines outcome

  /* The friend is unfrozen */
  if (res == 0)
  {
    printf("Wizard %c%d in room (%d,%d) unfreezes friend %c%d\n",
     self->team, self->id, 
	 room->x, room->y,
     other->team, other->id);

    /* Fill in */
  //probably sem_post the wizard *other thread, to bring it alive
  //wizard *other is set to status 0 -- ALIVE
  //printf("sem_post on other wizard...");
  sem_post(&(other->statusSem));
  //printf("semaphore posted.\n");
      return 1; //SUCCESS FREE WIZARD
    
  }

  /* The spell failed */
  printf("Wizard %c%d in room (%d,%d) fails to unfreeze friend %c%d\n",
	 self->team, self->id, 
	 room->x, room->y,
	 other->team, other->id);

  return 0;
}
