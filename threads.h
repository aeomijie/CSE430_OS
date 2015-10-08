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

//global queue *RunQ;

void start_thread(void (*function) (void)){
   //stack *s = malloc(sizeof()); //allocate a stack
   //TCB_t *t = malloc(sizeof(8192)); //allocate a TCB
   //init_TCB(t, f, s);
   //addQueue(RunQ,t);
}

void run(){
   ucontext_t parent; //get a place to store the main context, for faking
   getcontext(&parent); //magic queue
   swapcontext(&parent, &(RunQ->context)); //start the first thread
}

void yield(){
   //initialize curr, next;
   curr = RunQ;
   rotateQ(RunQ);
   next = RunQ;
   swapcontext(curr->context, next->context); 
}

#endif /*THREADS_H*/
