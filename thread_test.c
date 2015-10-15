/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#include "threads.h"

static int global = 0;

void func1();
void func2();

int main(int argc, char argv[]){
   //initialize RunQ
   InitQueue(&RunQ);

   //Start threads
   start_thread(&func1);
   start_thread(&func2);
   
   //call run from threads
   run();

   return 0;
}

void func1(){
   int local = 0;
   while(1){
      printf("Function one\tlocal: %d, global: %d\n", local, global);
      ++local;
      ++global;
      sleep(1);
      yield();
   }
}

void func2(){
   int local = 0;
   while(1){
      printf("Function two\tlocal: %d, global: %d\n", local, global);
      ++local;
      ++global;
      sleep(1);
      yield();
   }
}
