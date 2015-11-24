/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    | kgosse@asu.edu
**************************************************************************/

#ifndef Q_H
#define Q_H

//#include "TCB.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool ;

typedef struct node{
   int payload; //element data
}node_t;

typedef struct queue{
   node_t* item; //head of the queue
   struct queue *next, *prev;
}queue_t;

/*Constructor: creates an empty array queue pointed to variable head*/
void InitQueue(queue_t **q){
   /*If a queue doesn't exist, then make one*/
   *q = NULL;
}

/*Returns a pointer to a new q-element*/
queue_t* NewItem(){
   static int i = 0;
printf("NewItem\n");
   node_t* newItem = (node_t*)malloc(sizeof(node_t)); //allocate memory for a an element
   queue_t* newQ = (queue_t*)malloc(sizeof(queue_t));
printf("Seg fault?\n");
   newItem->payload = i;
   newQ->item = newItem;
printf("here???\n");
   ++i;

   return newQ;
}

/*Adds a queue item pointed to by item, to queue pointed to by head*/
bool AddQueue(queue_t **q, queue_t* item){
   /*Both q and the item exist and the queue isn't full*/
   if(item != NULL){
      if(*q == NULL){
         *q = item;
         (*q)->next = *q;
         (*q)->prev = *q;
         return true;
      }
      else{
         (*q)->prev->next = item;
         item->next = *q;
         item->prev = (*q)->prev;
         (*q)->prev = item;
         return true;
      }
   }
   return false;
}
 
void FreeItem(queue_t* item){
   free(item);
}

/*Deletes an item from head and returns a pointer to the deleted item*/
queue_t* DelQueue(queue_t **q){
   /*A queue with elements must exist to delete from*/
   if(*q != NULL){
      queue_t* item;
      /*If head is the only element in queue*/
      if((*q)->next == *q && (*q)->prev == *q){
         item = *q;
//         FreeItem(*q);
         *q = NULL;
      }
      else{
         item = *q;
         *q = (*q)->next;
         (*q)->prev = (*q)->prev->prev;
//         FreeItem((*q)->prev->next);
         (*q)->prev->next = *q;
      } 
      return item;
   }
   return NULL;
}

/*moves the header pointer to the next element in the queue*/
void RotateQ(queue_t **q) {
   /*If a queue exists and more than one element exists*/
   //if(q->head != NULL && q->head->next != q->head && q->head->prev != q->head){
  //    q = &((*q)->next);
   //}
   AddQueue(q, DelQueue(q));
}

#endif
