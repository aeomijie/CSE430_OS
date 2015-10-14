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

TCB_t *RunQ;

void start_thread(void (*function) (void)){
   void *s = malloc(sizeof(8192)); //allocate a stack
   TCB_t *t = malloc(sizeof(TCB_t)); //allocate a TCB
   init_TCB(t, function, s, 8192);
   AddQueue(&RunQ, t);
}

void run(){
   ucontext_t parent; //get a place to store the main context, for faking
   getcontext(&parent); //magic queue
   swapcontext(&parent, &(RunQ->context)); //start the first thread
}

void yield(){
   //initialize curr, next;
   TCB_t *curr, *next;
   curr  = RunQ;
   RotateQ(&RunQ);
   next = RunQ;
   swapcontext(&(curr->context), &(next->context));
}

#endif /*THREADS_H*/
