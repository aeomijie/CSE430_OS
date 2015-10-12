/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #2

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#ifndef TCB_H
#define TCB_H

#include <ucontext.h>
#include <string.h> //for memset

typedef struct TCB_t {
   struct TCB_t     *next;
   struct TCB_t     *prev;
   ucontext_t      context;
} TCB_t;


/*init_TCB: initialize TCB structure elements for a new thread*/
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size){
   memset(tcb, '\0', sizeof(TCB_t)); //clear tcb memory by setting to null
   getcontext(&tcb->context); //set a parent context
   tcb->context.uc_stack.ss_sp = stackP; //set the context's thread stack pointer
   tcb->context.uc_stack.ss_size = (size_t) stack_size; //set the context's stack size
   makecontext(&tcb->context, function, 0); //modify the context with the new user context parameters
}

#endif /*TCB_H*/
