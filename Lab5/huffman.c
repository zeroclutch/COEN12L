/*
This program uses Huffman coding. An efficient method is used to encode data to save memory.
*/
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

static NODE* mkNode(int data, NODE* left, NODE* right);
static void readFile(char* fileName);
static int depth(NODE* np);
static int nodeCmp(NODE* np1, NODE* np2);

// Queue
NODE* nodes[257];
// ASCII characters (indexed count)
int ascii[257];



static NODE* mkNode(int data, NODE* left, NODE* right){
  NODE* root = malloc(sizeof(NODE));
  assert(root != NULL);
  root->count = data;
  root->parent = NULL;
  if(left != NULL){
    left->parent = root;
  }
  if(right != NULL){
    right->parent = root;
  }
  return root;
}

static void readFile(char* fileName){
  FILE* fp = fopen(fileName, "r");
  if(fp == NULL){
    puts("Unable to open file. Check the file path and try again.");
    return;
  }

  int x = getc(fp);
  while(x != EOF){
    ascii[x]++;
    x = getc(fp);
  }

  fclose(fp);
  return;
}

/*
 * Finds the depth recursively
*/
static int depth(NODE* np){
  assert(np != NULL);
  if(np->parent == NULL){
    return 0;
  }
  return depth(np->parent) + 1;
}


/*
 * Finds the largest of two nodes
*/
static int nodeCmp(NODE* np1, NODE* np2){
  assert(np1 != NULL && np2 != NULL);
  return (np1->count < np2->count) ? -1 : (np1->count > np2->count);
}


int main(int argc, char* argv[]){
  if(argc == 2){
    puts("Missing and/or added insufficient number of files!");
    return 0;
  }
  else {
    readFile(argv[1]);
  }

  PQ *pq = createQueue(nodeCmp);
  for(int i = 0; i < 256; i++){
    if(ascii[i] > 0){
      nodes[i] = mkNode(ascii[i], NULL, NULL);
      addEntry(pq, nodes[i]);
    }
  }
  nodes[256] = mkNode(0, NULL, NULL);
  addEntry(pq, nodes[256]);
  while(numEntries(pq) > 1){
    NODE* right = removeEntry(pq);
    NODE* left = removeEntry(pq);
    NODE* parent = mkNode(left->count + right->count, left, right);
    addEntry(pq, parent);
  }

  for(int j = 0; j < 256; j++){ 
    if(nodes[j] != NULL){
      printf(isprint(j) ? "%c" : "%03o", j);
      printf(": %d x %d bits = %d bits\n", ascii[j], depth(nodes[j]), ascii[j]*depth(nodes[j]));
    }
  }

  pack(argv[1], argv[2], nodes);
  destroyQueue(pq);
  return 0;
}