/**************************************************************************
  2                         Arizona State University
  3                         CSE430 Operating Systems
  4                                 Project #4
  5 
  6                 Abigael Omijie | abigael.omijie@asu.edu
  7                 Katie Gosse    | kgosse@asu.edu
  8 **************************************************************************/

#include "sem.h"

// Arbitrary numbers - change as needed or whatever
#define R 4 // Max number of readers
#define W 2 // Max number of writers

int activeR = 0, activeW = 0; // To begin, no readers or writers are active
int waitR = R, waitW = W; // Which means all readers and writers are waiting
Sem_t *mutex, *Rsem, *Wsem;

void reader();
void writer();

int main (int argc, char argv[]){
   // Initialize semaphores
   InitSem(&mutex, 1);
   InitSem(&Rsem, R);
   InitSem(&Wsem, W);

   start_thread(&writer);
   start_thread(&writer);

   run();

   return 0;
}

void reader(){

}

void writer(){
   int i = 1;
   // Writer Entry
   P(&mutex); // Lock
   // Check if any readers or other writers are active
   if (activeR > 0 || activeW > 0) {
      printf("Writing process is waiting...\n");
      ++waitW; // Indicate another waiting writer
      V(&mutex); // Unlock mutex
      P(&Wsem); // Increment writing blocking Q
      P(&mutex); // Relock mutex
      --waitW; // Decrement active writer
      printf("Writing process is done waiting...\n");
   }
   ++activeW;
   V(&mutex);

   // Writer critical section
   printf("Writing...\n");
   // Writing..... Sleep for a few seconds
   sleep(3);
   printf("Done writing...\n");
   
   // Writer exit
   P(&mutex);
   --activeW; // Decrement an active writer
   if(waitR > 0){
      for(; i <= waitR; ++i){
         V(&Rsem);
      }
   }
   else if(waitW > 0){
      V(&Wsem);
   }
   V(&mutex);
}
