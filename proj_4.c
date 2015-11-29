/***********************************************************************
                          Arizona State University
                          CSE430 Operating Systems
                                  Project #4
  
                  Abigael Omijie | abigael.omijie@asu.edu
                  Katie Gosse    | kgosse@asu.edu
***********************************************************************/

#include "sem.h"

// Arbitrary numbers - change as needed or whatever
#define R 4 // Max number of readers
#define W 2 // Max number of writers

//char buff[200]; // Buffer for writing into and reading from

int global; // Global for buffer writing
int activeR, activeW; // To begin, no readers or writers are active
int waitR, waitW; // Which means all readers and writers are waiting
int MOD_VALUE = 1000;

Sem_t *mutex, *Rsem, *Wsem;



void reader();
void writer();

int main (int argc, char const *argv[]){
   // Initialize count variables
   activeR = 0;
   activeW = 0;
   waitR = 0;
   waitW = 0; 
   
   global = 0;

   // Initialize semaphores
   InitSem(&mutex, 1);
   InitSem(&Rsem, 1);
   InitSem(&Wsem, 1);
   
   // Initialize the RunQ
   InitQueue(&RunQ);

   // Add the threads to the run queue
   start_thread(&writer);
   start_thread(&reader);
  // start_thread(&reader);
   start_thread(&writer);
   start_thread(&reader);
   start_thread(&reader);
//   start_thread(&reader);

   // And it begins
   run();

   return 0;
}

void readerEntry(){
   // Reader entry
   P(&mutex); // Lock
   // Check if any writers are active or writing
   if(waitW > 0 || activeW > 0){
      printf("Reading process is waiting...\n");
      ++waitR; // Indicate another waiting reader
      V(&mutex); // Unlock 
      P(&Rsem); // Increment reading blocking Q
      //P(&mutex); // Lock
      --waitR; // Decrement waiting reader
      printf("Reading process is done waiting...\n");
   }
   ++activeR; // Indicate another active reader
   //V(&mutex); // Unlock  
   
   if(waitR > 0){
      V(&Rsem);
   }
   else{
      V(&mutex);
   }
}

void readerExit(){
   // Reader exit
   P(&mutex); // Lock
   --activeR; // Decrement the number of active readers
   if(activeR = 0 && waitW > 0){
      printf("Reader remainder section...\n");
      V(&Wsem);
      printf("Exit reader remainder section...\n");
   }
   else{
     V(&mutex);
   }
}

void reader(){
   while(1){
      // Reader critical section
      printf("Reading..\n");
      readerEntry();
      sleep(1);
      printf("global is %d\n", global);
      sleep(1);
      printf("Done reading.\n");
      sleep(1);
      readerExit();
   }
}
  
void writerEntry(){
   // Writer Entry
   P(&mutex); // Lock
   // Check if any readers or other writers are active
   if (activeR > 0 || activeW > 0) {
      printf("Writing process is waiting...\n");
      ++waitW; // Indicate another waiting writer
      V(&mutex); // Unlock mutex
      P(&Wsem); // Increment writing blocking Q
      //P(&mutex); // Relock mutex
      --waitW; // Decrement waiting writer
      printf("Writing process is done waiting.\n");
   }
   ++activeW;
   V(&mutex);
}

void writerExit(){
   // Writer exit
   P(&mutex);
   --activeW; // Decrement an active writer
   if(waitR > 0){
      printf("Writer remainder section for readers...\n");
      V(&Rsem);
      printf("Exiting writing remainder section...\n");
   }
   else if(waitW > 0){
      printf("Writer remainder section for writers...\n");
      V(&Wsem);
      printf("Exiting writer remainder section... \n");
   }
   else{
      V(&mutex);
   }
}

void writer(){
   srand(time(NULL));

   while(1){
      // Writer critical section
      printf("Writing...\n");
      sleep(1);
      writerEntry();
      global = (rand() % MOD_VALUE) + 1;
      printf("global is now changed to %d\n", global);
      sleep(1);
      printf("Done writing...\n");
      sleep(1);
      writerExit();
   }
}
