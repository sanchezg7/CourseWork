#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "cube.h"
#include "wizard.h"

//THIS FILE ONLY HAS THE WIZARD THREAD FUNCTION
//wizards represents threads and they will run this, infinitely
//the semaphore will stop the wizard from running

void *
wizard_func(void *wizard_descr)
{
  struct cube* cube;
  struct room *newroom; 
  struct room *oldroom; 
  struct wizard* self; 		//represents itself	
  struct wizard* other;		//represents the other wizard in the current room

  //make(initialize) the statusSemaphore 1
  //sem_init(&(self->statusSem), 0, 1); //Wizard initialized to ONE
  
  int semvalue;  //debugging purposes

  
  self = (struct wizard*)wizard_descr;
  assert(self);
  cube = self->cube;
  assert(cube);
  
  //force a sem_wait to freeze the thread, ONLY one wizard at a time
  sem_getvalue(&wizardMutex, &semvalue);
  //printf("In wizard(%c%d) thread, putting my self to sleep. semvalue before wait: %d\n", self->team, self->id, semvalue);
  sem_wait(&wizardMutex);

  /* Sets starting room */
  oldroom = cube->rooms[self->x][self->y];
  assert(oldroom);
  
  /* Chooses the new room */
  newroom = choose_room(self);

  /* Infinite loop */
  while (1)
  {
      
      /* Loops until he's able to get a hold on both the old and new rooms */
      while (1)
	    {
	      printf("Wizard %c%d in room (%d,%d) wants to go to room (%d,%d)\n",
		     self->team, self->id, oldroom->x, oldroom->y, newroom->x, newroom->y);
	      

	      if (try_room(self, oldroom, newroom)) //return 1 if the room is full
        {
          /* Waits a random amount of time */
          dostuff();
          
          /* Chooses the new room */
          //printf("Wizard %c%d choosing a new room", self->team, self->id);
          newroom = choose_room(self); //declare another room to try
          
          /* Goes back to the initial state and try again */
          continue;
        }
	      else
        {
          //printf("Found a valid room!\n");
          break; //Wizard found a VALID room
        }
	    }
      
      printf("Wizard %c%d in room (%d,%d) moves to room (%d,%d)\n",
	     self->team, self->id, 
	     oldroom->x, oldroom->y, newroom->x, newroom->y);

      /* Fill in */
      
      /* Self is active and has control over both rooms */
      switch_rooms(self, oldroom, newroom);

      //find opponent to battle
      other = find_opponent(self, newroom);

      /* If there is not another wizard does nothing */
      if (other == NULL)
	    {
	      printf("Wizard %c%d in room (%d,%d) finds nobody around \n",
		     self->team, self->id, newroom->x, newroom->y);
	      /* Fill in */
	    }
      else
	    {
        //printf("There is someone else in the room.\n");
	      /* Other is from opposite team */
	      if (other->team != self->team)
        {

          /* Checks if the opponent is active */
          if (other->status == 0)
		      {
		        printf("Wizard %c%d in room (%d,%d) finds active enemy\n",
			       self->team, self->id, newroom->x, newroom->y);

		        if(fight_wizard(self, other, newroom))
            {
              //self freeze
              //wizard *self set to status 1 -- FROZEN
              //sem_wait on the self wizard thread, block thread
              self->status = 1; //SELF FROZEN
              sem_getvalue(&(self->statusSem), &semvalue);
              //printf("Self wizard will be frozen. status: %d, statusSem before the wait: %d sem_wait on self wizard...", self->status, semvalue);
              sem_wait(&(self->statusSem));
              sem_getvalue(&(self->statusSem), &semvalue);
              //printf("sem_wait complete on self wizard. statusSem after the wait: %d\n", semvalue);
            }
            else {
              //enemy freeze
              //wizard *other gets status 1 -- FROZEN
              //sem_wait on the other wizard thread, block the thread
              other->status = 1; //OTHER FROZEN
              sem_getvalue(&(other->statusSem), &semvalue);              
              //printf("Other wizard will be frozen. status: %d (Should be 1 -- FROZEN), statusSem before the sem_wait: %d sem_wait on other wizard...", other->status, semvalue);
              sem_wait(&(other->statusSem));
              sem_getvalue(&(other->statusSem), &semvalue);
              //printf("sem_wait complete on other wizard. statusSem after the sem_wait: %d\n", semvalue);

            }
		      }
          else
	        {
	          printf("Wizard %c%d in room (%d,%d) finds enemy already frozen\n",
		         self->team, self->id, newroom->x, newroom->y);
	        }
        }
	      /* Other is from same team */
	      else
        {
          /* Checks if the friend is frozen */
          if (other->status == 1)
	        {
	          if(free_wizard(self, other, newroom))
            {
              //success
              //printf("Free Wizard! sem_post on friend Wizard (%c%d)\n", other->team, other->id);
              other->status = 0; //ACTIVE status
              sem_post(&(other->statusSem));
              sem_getvalue(&(other->statusSem), &semvalue);
              //printf("sem_post on FRIEND WIZARD. other statusSem after post: %d\n", semvalue);
            }
	        } else { //friend wizard is ACTIVE
               /* Fill in */ 
              //wizards do nothing and brag about their stuff
              //printf("both wizards are friend and they are ACTIVE\n");
              //printf("%c%d status %d, %c%d status %d\n", self->team, self->id, self->status, other->team, other->id, other->status);
              dostuff();
            }
        }

	    }
      
      turnFlag = 0;   //TURN FINISHED for WIZARD

      sem_getvalue(&wizardMutex, &semvalue);
      //printf("Wizard %c%d turn is over. sem_wait(wizardMutex)\n", self->team, self->id);

      sem_post(&intWizMutex); //wake the interface back up
      sem_wait(&wizardMutex); //thread to sleep, relinquish turn

      /* Thinks about what to do next */
      dostuff();
      //wizard AWAKES 

      //printf("Wizard %c%d; Before while loop, status: %d\n", self->team, self->id, self->status);
      while(self->status ==1) //FROZEN
      {
        //printf("Wizard %c%d is still frozen!\n", self->team, self->id);
        turnFlag = 0;
        sem_post(&intWizMutex); //bring interface back up
        //interface will post another wizard
       //do a sem_wait on the statusSem to freeze it if it was set to 0 previously, this will freeze the semaphore
        sem_wait(&(self->statusSem)); //put to sleep if frozen (0)
      } 
            
//      sem_post(&(self->statusSem)); //Wizard ACTIVE and restore sem back to 1
      sem_getvalue(&(self->statusSem), &semvalue);
      //printf("Wizard %c%d turn is back! semvalue: %d\n", self->team, self->id, semvalue);
      oldroom = newroom;
      newroom = choose_room(self);
    }
  
  return NULL;
}

