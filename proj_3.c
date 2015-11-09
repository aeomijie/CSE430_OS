/**************************************************************************
			Arizona State University
		        CSE430: Operation Systems
			     Project #3
		 Abigael Omijie | abigael.omijie@asu.edu
		 Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#include "threads.h"
#include "sem.h"
#include <stdlib.h> // For rand()

#define BUFF_SZ 4 // Buffer size
Sem_t *full, *empty;
int buffer[BUFF_SZ];
//int item = 0;
int in = 0, out = 0;

void producer();
void consumer();
void putItem(int item);
int getItem();

int main (int argc, char argv[]){
   // Initialize semephores full and empty
   InitSem(&full, 0);
   InitSem(&empty, BUFF_SZ);

   // Start producer and consumer threads
   start_thread(&producer);
   start_thread(&producer);
   start_thread(&consumer);
   start_thread(&consumer);

   // And run
   run();

   return 0;
}

//producer
void producer(){
   int item;
   while (1){
      item = (rand() % 100) + 1; // Random num b/t 1 and 100
      printf("Producer created item %d\n", item);
      putItem(item);
      sleep(1);
   }
}

//consumer
void consumer(){
   int item;
   while (1){
      item = getItem();
      printf("Consumer used item %d\n", item);
      sleep(1);
   }
}

void putItem(int item){
   P(&empty);
   buffer[in] = item;
   in = (in + 1) % BUFF_SZ;
   V(&full);
}

int getItem(){
   P(&full);
   int temp = buffer[out];
   out = (out + 1) % BUFF_SZ;
   V(&empty);
   return temp;
}
