/*
 * This uses a priority queue that simulates a min heap
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

static int leftNode(int i);
static int rightNode(int i);
static int parentNode(int i);


// Helper functions
static int parentNode(int i) {
  return (i-1)/2;
}

static int leftNode(int i) {
  return (i*2)+1;
}

static int rightNode(int i) {
  return (i*2)+2;
}

struct pqueue {
  int count;
  int length;
  void** data;
  // Comparison function
  int (*compare)();
};

/**
 * Create a priority queue object
 * O(1)
 */
PQ *createQueue(int (*compare)()){
  PQ *pq = malloc(sizeof(PQ));
  assert(pq != NULL);
  pq->compare = compare;
  pq->count = 0;
  pq->length = 10;
  pq->data = malloc(sizeof(void*)*10);
  assert(pq->data != NULL);
  return pq;
}

/**
 * Destroys the priority queue
 * O(n)
 */
void destroyQueue(PQ *pq){
  assert(pq != NULL);

  // Free members
  for(int i = 0; i < pq->count; i++){
    free(pq->data[i]);
  }
  free(pq->data);
  free(pq);
}

/**
 * Returns the size of the priority queue
 * O(1)
 */
int numEntries(PQ *pq){
  assert(pq != NULL);
  return pq->count;
}

/**
 * Inserts an entry to the priority queue
 * O(log(n))
 */
void addEntry(PQ *pq, void *entry){
  assert(pq != NULL);

  // If we have reached the maximum, double the max length and copy over the data
  if(pq->count == pq->length) {
    pq->length *= 2;
    pq->data = realloc(pq->data, sizeof(void*) * pq->length);
  }

  pq->data[pq->count] = entry;
  int index = pq->count;

  // Swap the child with the parents if child < parent
  while(pq->count != 0 && (*pq->compare)(pq->data[parentNode(index)], pq->data[index]) > 0){
    void* temp = pq->data[index];
    pq->data[index] = pq->data[parentNode(index)];
    pq->data[parentNode(index)] = temp;
    index = parentNode(index);
  }
  pq->count++;
}

/**
 * Removes an entry from the priority queue
 * O(log(n))
 */
void *removeEntry(PQ *pq){
    assert(pq != NULL);
    assert(pq->count > 0);

    // Swap root and last item
    void* response = pq->data[0];
    pq->data[0] = pq->data[pq->count - 1];
    int index = 0;

    // Iterate until the left child no longer exists
    while( pq->count - 1 >= leftNode(index)) {
      int smallestChild = leftNode(index);
      if(pq->count - 1 >= rightNode(index)) {
        // Use smaller child
        if((*pq->compare)(pq->data[rightNode(index)], pq->data[leftNode(index)]) < 0){
            smallestChild = rightNode(index);
        }
      }
      if((*pq->compare)(pq->data[index], pq->data[smallestChild]) >= 0) {
        void* swapData = pq->data[index];
        pq->data[index] = pq->data[smallestChild];
        pq->data[smallestChild] = swapData;
      }
      else{
          break;
      }
      index = smallestChild;
    }
    pq->count--;
    return response;
}
