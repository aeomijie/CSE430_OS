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

typedef struct node{
   int x; //payload 
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
//NewItem();

/*adds a queue item pointed to by item, to queue pointed to by head*/
//AddQueue(&head, item);

/*deletes an item from head and returns a pointer to the deleted item*/
//DelQueue(&head);

/*moves the header pointer to the next element in the queue*/
//RotateQ(&head);


#endif
