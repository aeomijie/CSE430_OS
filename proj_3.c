/**************************************************************************
			Arizona State University
		        CSE430: Operation Systems
			     Project #3
		 Abigael Omijie | abigael.omijie@asu.edu
		 Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#include "sem.h"
#include <stdlib.h> // For rand()
#include <time.h>

#define BUFF_SZ 4 // Buffer size


Sem_t *full, *empty, *mutex;

int buffer[BUFF_SZ];
int in = 0, out = 0;
int counter = 0;


void producer();
void consumer();
void putItem(int item);
int getItem();

int main (int argc, char *argv[]){
   
   //Initialize RunQ
   InitQueue(&RunQ);

   // Initialize semephores full and empty
   InitSem(&full, 0);
   InitSem(&empty, BUFF_SZ);
   InitSem(&mutex, 1);

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
   srand(time(NULL));
   sleep(1);

   printf("producer: Thread started.\n");
   sleep(1);

   while (1){
      int item = (rand() % 100) + 1; // Random num b/t 1 and 100
      printf("Producer created item %d\n", item);
      sleep(1);

      printf("Producer: Trying to enter CS\n");
      sleep(1);

      P(&empty);
      P(&mutex);

      printf("Producer: Entering the CS\n");  
      sleep(1);

      buffer[in] = item;
      printf("Producer: item is in the buffer.\n", item);
      sleep(1);
      
      in = (in + 1) % BUFF_SZ;
      printf("Buffer in position set to %d \n", in);
      sleep(1);

      counter++;
      printf("Producer: The counter was incremented to %d \n", counter);
      sleep(1);

      printf("Producer: Getting context switched\n");
      sleep(1);
      yield();

      printf("Producer: Leaving CS\n");
      sleep(1);

      V(&mutex);
      V(&full);
   }
}

//consumer
void consumer(){
   int consume=0;
   printf("Consumer: Thread started\n");
   sleep(1);

   while (1){
      printf("Consumer: Trying to enter the CS\n");
      
      P(&full);
      P(&mutex);     

      printf("Consumer: Entering the CS\n");
      sleep(1);

      consume = buffer[out];
      printf("Consumer: Got item from the buffer: %d \n", consume);
      sleep(1);

      out = (out + 1) % BUFF_SZ;
      printf("Consumer: Buffer out position set to %d \n", out);
      sleep(1);

      counter--;
      printf("Consumer: counter decremented to %d \n", counter);
      sleep(1);
      
      V(&mutex);
      V(&empty);

      printf("Consumer: Consumed item\n");
      sleep(1);
   }
}
/*
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
}*/
