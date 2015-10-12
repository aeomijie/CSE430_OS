/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #2

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#ifndef THREADS_H
#define THREADS_H

#include "q.h"

//global header pointer for queue
queue_t *RunQ;

void start_thread(void (*function) (void)){
   void *stack = malloc(sizeof(8192)); //allocate a stack
   TCB_t *t = malloc(sizeof(TCB_t)); //allocate a TCB
   init_TCB(t, function, stack, 8192);
   AddQueue(RunQ, t);
}

void run(){
   ucontext_t parent; //get a place to store the main context, for faking
   getcontext(&parent); //magic queue 
   swapcontext(&parent, &(RunQ->head->context)); //start the first thread
}

void yield(){
   //initialize curr, next;
   queue_t *curr, *next;
   curr  = RunQ;
   RotateQ(RunQ);
   next = RunQ;
   swapcontext(&(curr->head->context), &(next->head->context)); 
}

#endif /*THREADS_H*/
