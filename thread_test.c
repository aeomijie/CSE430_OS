/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#include "threads.h"

/*Write  a driver program in a file called thread_test.c. Into thread_test.c.c include threads.h which includes q.h, which includes TCB.h, which includes ucontext.h.
Declare a global RunQ.
Write a few functions with infinite loops (put a yield in each loop). Note: try to write thread functions that are meaningful, use global and local variables
In main, initialize RunQ, start threads using the functions you defined using start_thread.
Call run() and watch.
Call friends and family*/

TCB_t *RunQ;
static int global = 0;

void *func1();
void *func2();

int main(int argc, char argv[]){
   //initialize RunQ
   InitQueue(RunQ);

   //Start threads
   start_thread(func1());
   start_thread(func2());
   
   //call run from threads
   run();

   return 0;
}

void *func1(){
   static int local = 0;
   printf("func1\tstatic int local = 0;\n");
   printf("Function one - local: %d, global: %d\n", local, global);
   ++local;
   printf("func1\t++local;\n");
   ++global;
   printf("func1\t++global;\n");
   sleep(1);
   printf("func1\tsleep(1);\n");
   yield();
   printf("func1\tyield()\n");
}

void *func2(){
   static int local = 0;
   printf("Function two - local: %d, global: %d\n", local, global);
   ++local;
   ++global;
   sleep(1);
   yield();
}
