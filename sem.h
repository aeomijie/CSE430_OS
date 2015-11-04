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
   int lock;
   //q->delQ;

} Sem_t;

//Initializes the value field with the specified value
void InitSem(S, value){
   //sem.count = value;
}

void P(S){
   //sem.count--;
   if(sem.count < 0){
       //temp = delQ(RunQ);
       //addQ(sem.Q, temp);
       //swapcontext(RunQ->head, sem->Q->..)
}

void V(S){
   //sem.count++;
   if(S.count <= 0){
      //temp = delQ(sem->Q);
      //addQ(RunQ, delQ(S.Q));
   }
   yield();
}

#endif //SEM_H



