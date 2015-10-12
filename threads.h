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
TCB_t *RunQ;


void start_thread(void (*function) (void)){
   printf("start_thread\n");
   void *s = malloc(sizeof(8192)); //allocate a stack
   printf("start_thread\tvoid *stack = malloc(sizeof(8192));\n");
   TCB_t *t = malloc(sizeof(TCB_t)); //allocate a TCB
   printf("start_thread\tTCB_t *stack = malloc(sizeof(TCB_t));\n");
   init_TCB(t, function, s, 8192);
   printf("start_thread\tinit_TCB(t, function, stack, 8192);\n");
   AddQueue(RunQ, t);
   printf("start_thread\tAddQueue(RunQ, t);\n\n");
}

void run(){
   ucontext_t parent; //get a place to store the main context, for faking
   printf("run\tucontext_t parent;\n");
   getcontext(&parent); //magic queue
   printf("run\tgetcontext(&parent);\n");

   /* Segmentation fault somewhere here */

   swapcontext(&parent, &(RunQ->context)); //start the first thread
   printf("run\tswapcontext(&parent, &(RunQ->head->context));\n");
}

void yield(){
   //initialize curr, next;
   TCB_t *curr, *next;
   printf("yield\tqueue_t *curr, *next;\n");
   curr  = RunQ;
   printf("yield\tcurr = RunQ;\n");
   RotateQ(RunQ);
   printf("yield\tRotateQ(RunQ);\n");
   next = RunQ;
   printf("yield\tnext = RunQ;\n");

   /*Segmentation fault somewhere here*/

   swapcontext(&(curr->context), &(next->context));
   printf("yield\tswapcontext(&(curr->head->context), &(next->head->context));\n");
}

#endif /*THREADS_H*/
