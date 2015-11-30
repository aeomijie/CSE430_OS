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
#define MOD 1000 // Modulus value for rand

char buff[200]; // Buffer for writing into and reading from
int activeR, activeW; // To begin, no readers or writers are active
int waitR, waitW; // Which means all readers and writers are waiting

Sem_t *mutex, *Rsem, *Wsem;

void readerEntry();
void readerExit();
void reader();
void writerEntry();
void writerExit();
void writer();

int main (int argc, char const *argv[]){
   // Initialize count variables
   activeR = 0;
   activeW = 0;
   waitR = 0;
   waitW = 0;

   // Initialize semaphores
   InitSem(&mutex, 1);
   InitSem(&Rsem, 1);
   InitSem(&Wsem, 1);
   
   // Initialize the RunQ
   InitQueue(&RunQ);

   // Add the threads to the run queue
   start_thread(&writer);
   start_thread(&reader);
   start_thread(&writer);
   start_thread(&reader);
   start_thread(&reader);

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
      sleep(1);
      waitR++; // Indicate another waiting reader
      V(&mutex); // Unlock 
      P(&Rsem); // Increment reading blocking Q
      waitR--; // Decrement waiting reader
      printf("Reading process is done waiting.\n");
      sleep(1);
   }
   activeR++; // Indicate another active reader
   
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
   activeR--; // Decrement the number of active readers
   if(activeR == 0 && waitW > 0){
      printf("Entering reader remainder section...\n");
      sleep(1);
      V(&Wsem);
      printf("Exiting reader remainder section.\n");
      sleep(1);
   }
   else{
      V(&mutex);
   }
}

void reader(){
   while(1){
      // Reader critical section
      readerEntry();
      printf("Reading from buffer...\n");
      sleep(1);
      printf("%s\n", buff);
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
      sleep(1);
      waitW++; // Indicate another waiting writer
      V(&mutex); // Unlock mutex
      P(&Wsem); // Increment writing blocking Q
      P(&mutex); // Relock mutex ?????????????????
      waitW--; // Decrement waiting writer
      printf("Writing process is done waiting.\n");
      sleep(1);
   }
   activeW++;
   V(&mutex);
}

void writerExit(){
   int i;
   // Writer exit
   P(&mutex);
   activeW--; // Decrement an active writer
   if(waitR > 0){
      printf("Writer remainder section for readers...\n");
      sleep(1);
      for(i = 0; i < waitR; i++){
         V(&Rsem);
      }
      printf("Exiting writing remainder section.\n");
      sleep(1);
   }
   else if(waitW > 0){
      printf("Writer remainder section for writers...\n");
      sleep(1);
      V(&Wsem);
      printf("Exiting writer remainder section.\n");
      sleep(1);
   }
   else{
      V(&mutex);
   }
}

void writer(){
   srand(time(NULL));
   int num = 0;

   while(1){
      writerEntry();
      printf("Writing to buffer...\n");
      sleep(1);
      num = (rand() % MOD) + 1;
      sprintf(buff, "Random number is now %d", num);
      printf("Writer wrote random number %d to buffer.\n", num);
      sleep(1);
      printf("Done writing.\n");
      sleep(1);
      writerExit();
   }
}
