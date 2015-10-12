/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#ifndef Q_H
#define Q_H

#include "TCB.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool ;

// Need to use TCB_t, instead of node
/*typedef struct node{
   int payload; //element data
   struct node *prev, *next; //ptrs for each element
}node_t;*/

typedef struct queue{
   TCB_t* head; //head of the queue
   int currSize; //current number of items in queue
   int maxSize; //max number of items in queue
}queue_t;

/*Constructor: creates an empty array queue pointed to variable head*/
void InitQueue(queue_t *q){
   /*If a queue doesn't exist, then make one*/
   if(q != NULL){
      q->head = NULL;
      q->currSize = 0;
      q->maxSize = 10;
   }
}

//Is this function needed now???
/*Returns a pointer to a new q-element*/
/*TCB_t* NewItem(){
   static int i = 0;
   TCB_t* item = (TCB_t*)malloc(sizeof(TCB_t)); //allocate memory for a an element 
   item->payload = i;
   item->next = NULL;
   item->prev = NULL;
   ++i;

   return item;
}*/

/*Adds a queue item pointed to by item, to queue pointed to by head*/
bool AddQueue(queue_t *q, TCB_t* item){
   /*Both q and the item exist and the queue isn't full*/
   if(q != NULL && item != NULL && q->currSize != q->maxSize){
      if(q->head == NULL){
         q->head = item;
         q->head->next = q->head;
         q->head->prev = q->head;
         ++q->currSize;
         return true;
      }
      else{
         q->head->prev->next = item;
         item->next = q->head;
         item->prev = q->head->prev;
         q->head->prev = item;
         ++q->currSize;
         return true;
      }
   }
   return false;
}
 
void FreeItem(TCB_t* item){
   free(item);
}

/*Deletes an item from head and returns a pointer to the deleted item*/
TCB_t* DelQueue(queue_t *q){
   /*A queue with elements must exist to delete from*/
   if(q->head != NULL){
      TCB_t* item;
      /*If head is the only element in queue*/
      if(q->head->next == q->head && q->head->prev == q->head){
         item = q->head;
         FreeItem(q->head);
         q->head = NULL;
      }
      else{
         item = q->head;
         q->head = q->head->next;
         q->head->prev = q->head->prev->prev;
         FreeItem(q->head->prev->next);
         q->head->prev->next = q->head;
      } 
      return item;
   }
   return NULL;
}

/*moves the header pointer to the next element in the queue*/
void RotateQ(queue_t *q) {
   /*If a queue exists and more than one element exists*/
   if(q->head != NULL && q->head->next != q->head && q->head->prev != q->head){
      q->head = q->head->next;
   }
}

#endif
