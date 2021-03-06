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

/*Constructor: creates an empty array queue pointed to variable head*/
void InitQueue(TCB_t **q){
   //Create a queue
   *q = NULL; 
}

/*Returns a pointer to a new q-element*/
TCB_t* NewItem(){
   TCB_t* item = (TCB_t*)malloc(sizeof(TCB_t)); //allocate memory for a an element 
   item->next = NULL;
   item->prev = NULL;

   return item;
}

/*Adds a queue item pointed to by item, to queue pointed to by head*/
void AddQueue(TCB_t **q, TCB_t* item){
  if(item != NULL){
      if(*q == NULL){
         *q = item;
         (*q)->next = *q;
         (*q)->prev = *q;
      }
      else{
         TCB_t* temp = *q;
         while(temp->next != *q)
            temp = temp->next;
         (*q)->prev = item;
         temp->next = item;
         item->prev = temp;
         item->next = *q;
         /*(*q)->prev->next = item;
         item->next = *q;
         item->prev = (*q)->prev;
         (*q)->prev = item;*/
         
      }
   }
}
 
/*Deletes an item from head and returns a pointer to the deleted item*/
TCB_t* DelQueue(TCB_t **q){
   /*A queue with elements must exist to delete from*/
   if(*q != NULL){
      TCB_t* item;
      /*If head is the only element in queue*/
      if((*q)->next == *q && (*q)->prev == *q){
         item = *q;
         *q = NULL;
      }
      else{
         item = *q;
         *q = (*q)->next;
         (*q)->prev = (*q)->prev->prev;
         (*q)->prev->next = *q;
      } 
      return item;
   }
   return NULL;
}

/*moves the header pointer to the next element in the queue*/
void RotateQ(TCB_t **q) {
   /*If a queue exists and more than one element exists*/
   if(*q != NULL)
      AddQueue(q, DelQueue(q));
}

#endif
