/*************************************************************************
			Arizona State University
			CSE430: Operating Systems
			     Project #3
		Abigael Omijie | abigael.omijie@asu.edu
		Katie Gosse    | kgosse@asu.edu
*************************************************************************/
#ifndef SEM_H
#define SEM_H

#include "threads.h"

//Semaphore data structure
typedef struct Sem_t {
   int count;
   TCB_t *queue;

} Sem_t;

//Initializes the value field with the specified value
void InitSem(Sem_t **S, int value){
   *S = malloc(1, sizeof(Sem_t));
   (*S)->count = value;
   InitQueue(&((*S)->queue));
}

//Decrements a sempahores count and waits enter the RunQ
void P(Sem_t **S){
   *S->count--;
   if((*S)->count < 0){
       TCB_t *currProcess = DelQueue(&RunQ);
       AddQueue(&((*S)->queue) , &currentProcess);
       swapcontext(&(currProcess->context) , &(RunQ->context))
}

//Increments a semaphores count, wakes up the next waiting semaphore,
//and yields to the next process
void V(Sem_t **S){
   *S->count++;
   if((*S)->count <= 0){
      TCB_t *blockedProcess = DelQueue(&((*S)->queue));
      AddQueue(&RunQ, &blockedProcess);
   }
   yield();
}

#endif //SEM_H



