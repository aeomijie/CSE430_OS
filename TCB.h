/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#ifndef TCB_H
#define TCB_H

#include <ucontext.h>

typedef struct TCB_t {
   struct TCB_t     *next;
   struct TCB_t     *prev;
   ucontext_t      context;
} TCB_t;


/*init_TCB: initialize TCB structure elements for a new thread*/
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size){
   /*clear tcb memory by setting to null*/
   memset(tcb, '\0', sizeof(TCB_t));
   /*set a parent context*/
   getcontext(&tcb->context);
   /*set the context's thread stack pointer*/
   tcb->context.uc_stack.ss_sp = stackP;
   /*set the context's stack size*/
   tcb->context.uc_stack.ss_size = (size_t) stack_size;
   /*modify the context with the new user context parameters*/
   makecontext(&tcb->context, function, 0);
}

#endif /*TCB_H*/
