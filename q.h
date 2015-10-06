/**************************************************************************
                        Arizona State University
                        CSE430 Operating Systems
                                Project #1

                Abigael Omijie | abigael.omijie@asu.edu
                Katie Gosse    |
**************************************************************************/

#ifndef Q_H
#define Q_H
#include <stdlib.h>
#include <stdio.h>

typedef enum { false, true } bool ;

typedef struct node{
   int payload; //data 
   struct node *prev;
   struct node *next;
}node;

typedef struct queue{
   node *head; //oldest element in the queue
   node *tail; //newest element in the queue
   int currSize; //current size of the queue
   int maxSize; //max size of the queue
}queue;

/*Constructor: creates an empty array queue pointed to variable head*/
void InitQueue(queue *q){
   if(q != NULL){
      q->head = NULL;
      q->tail = NULL;
      q->currSize = 0;
      q->maxSize = 10;
   }
}

/*returns a pointer to a new q-element*/
node* NewItem(){
   node* item = (node*) malloc(sizeof(node)); //allocate memory for a node 
   item->payload = 0;
   item->next = NULL;
   item->prev = NULL;

   return item;    
}

//checks to see if the queue is empty
bool isEmpty(queue *q){
   if(q != NULL && q->head != NULL)
      return false;
   else
      return true;
}

/*adds a queue item pointed to by item, to queue pointed to by head*/
void AddQueue(queue *q, node* item){
   if(q != NULL && item != NULL){
      if(!isEmpty(q)){
        if(q->currSize == q->maxSize){ //when the q is full
  	   q->head->payload = item->payload;
	   q->head = q->head->next;
	}
	else{ //non-empty queue with room available
	   item->prev = q->tail;
           item->next = q->head;
           q->tail->next = item;
           q->head->prev = item;
           q->tail = item;
	} 
      }
      else{ //if the queue is empty
	   item->prev = NULL;
	   item->next = NULL;
	   q->head = item;
	   q->tail = item;
      }
   }
} 

/*deletes an item from head and returns a pointer to the deleted item*/
DelQueue(queue *q){
   if(!isEmpty(q)){
      if(currSize == 1){ //if queue has only one item
         free (item);
	 q->head = NULL;
	 q->tail = NULL;
      }
      else{ //if queue has more than one item
         
       }
   }
}

/*moves the header pointer to the next element in the queue*/
RotateQ(&head) {
   /*if the queue has 2 items*/
   if(queue.currSize == 2){
      node *temp;
      temp = queue->head;
      queue->head = queue->tail;
   }
   /*if the queue has 3 or more items*/
   else if(queue.currSize >= 3){
      queue->head = queue->tail;
      queue->tail = queue->tail->prev;
   }
}

#endif
