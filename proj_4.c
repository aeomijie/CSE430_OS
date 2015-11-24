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
#define R 5 // Max number of readers
#define W 5 // Max number of writers

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

   return 0;
}

void reader(){

}

void writer(){
   P(&mutex); // Lock
   // Check if any readers or other writers are active
   if (activeR > 0 || activeW > 0) {
       // wait
   }
}
