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

char buff[200]; // Buffer for writing into and reading from
int global = 0; // Global for buffer writing
int activeR = 0, activeW = 0; // To begin, no readers or writers are active
int waitR = 0, waitW = 0; // Which means all readers and writers are waiting
Sem_t *mutex, *Rsem, *Wsem;

void reader();
void writer();

int main (int argc, char argv[]){
   // Initialize semaphores
   InitSem(&mutex, 1);
   InitSem(&Rsem, R);
   InitSem(&Wsem, W);

   start_thread(&writer);
   start_thread(&reader);
   start_thread(&writer);
   start_thread(&reader);
   start_thread(&reader);
   //start_thread(&reader);

   run();

   return 0;
}

void reader(){
   // Reader entry
   P(&mutex); // Lock
   // Check if any writers are active or writing
   if(waitW > 0 || activeW > 0){
      printf("Reading process is waiting...\n");
      ++waitR; // Indicate another waiting reader
      V(&mutex); // Unlock 
      P(&Rsem); // Increment reading blocking Q
      P(&mutex); // Lock
      --waitR; // Decrement waiting reader
      printf("Reading process is done waiting...\n");
   }
   ++activeR; // Indicate another active reader
   V(&mutex); // Unlock  

   // Reader critical section
   printf("Reading...\n");
   printf("Buffer says: %s\n", buff);
   printf("Done reading...\n");

   // Reader exit
   P(&mutex); // Lock
   --activeR; // Decrement the number of active readers
   if(activeR = 0 && waitW > 0){
      printf("Reader remainder section...\n");
      V(&Wsem);
      printf("Exit reader remainder section...\n");
   }
   V(&mutex);
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
      --waitW; // Decrement waiting writer
      printf("Writing process is done waiting...\n");
   }
   ++activeW;
   V(&mutex);

   // Writer critical section
   printf("Writing...\n");
   sprintf(buff, "global is now %d", global);
   ++global;
   printf("Done writing...\n");
   
   // Writer exit
   P(&mutex);
   --activeW; // Decrement an active writer
   if(waitR > 0){
      printf("Writer remainder section for readers...\n");
      for(; i <= waitR; ++i){
         V(&Rsem);
      }
      printf("Exiting writing remainder section...\n");
   }
   else if(waitW > 0){
      printf("Writer remainder section for writers...\n");
      V(&Wsem);
      printf("Exiting writer remainder section... \n");
   }
   V(&mutex);
}
