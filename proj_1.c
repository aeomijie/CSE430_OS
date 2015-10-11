/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#include "q.h"
#include <stdio.h>
#include <stdlib.h>

void printQ(queue_t* q);

int main(int argc, char** argv){
   //Add three elements to queue Q1, and then add 3 more to queue Q2.
   //Rotate each Q twice. Delete elements from each q, one by one and print values till the queues are empty.
   //Repeat the above test again.

   queue_t q1, q2;
   node_t* item;
   int i = 0;

   InitQueue(&q1);
   InitQueue(&q2);

   do{
      item = NewItem();
      AddQueue(&q1, item);
      item = NewItem();
      AddQueue(&q2, item);
      item = NewItem();
      AddQueue(&q1, item);
      item = NewItem();
      AddQueue(&q2, item);
      item = NewItem();
      AddQueue(&q1, item);
      item = NewItem();
      AddQueue(&q2, item);
   
      printf("Printing q1.\n");
      printQ(&q1);
      printf("Printing q2.\n");
      printQ(&q2);

      RotateQ(&q1);
      RotateQ(&q1);
      RotateQ(&q2);
      RotateQ(&q2);

      printf("Printing q1 after rotating 2 times.\n");
      printQ(&q1);
      printf("Printing q2 after rotating 2 times.\n");
      printQ(&q2);

      do{
         item = DelQueue(&q1);
         printf("Printing q1 after deleting one element.\n");
         printQ(&q1);
      }while(item != NULL);

      do{
         item = DelQueue(&q2);
         printf("Printing q2 after deleting one element.\n");
         printQ(&q2);
      }while(item != NULL);

      ++i;
   }while(i < 2);
   return 0;
}

void printQ(queue_t* q){
   if(q->head != NULL){
      node_t* traverse = q->head;
      printf("Payload: %d\n", traverse->payload);
      traverse = traverse->next;
      while(traverse != q->head){
         printf("Payload: %d\n", traverse->payload);
         traverse = traverse->next;
      }
   }
   else
      printf("Queue is empty.\n");
}
