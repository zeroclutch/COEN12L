# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "list.h"

typedef struct node NODE;

struct node {
    void *value;
    NODE *prev;
    NODE *next;
} NODE;

struct list {
    int count;   
    NODE *head;
    NODE *tail;
    int (*compare)();
} LIST;

// Creates complete list
// O(1)
LIST *createList(int (*compare) ())
{
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->next = lp->head;    
	lp->head->prev = lp->head;    
	return lp;
}

// Destroys complete list
// O(n)
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;
	do
	{
		pNext = pDel->next;
		free(pDel);
		pDel = pNext;
	} while (pDel != lp->head);
	free(lp);
}

//Returns number of items
// O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);
    	return (lp->count);
}

//Adds elt to front of list
// O(1)
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));
	temp->data = item;
	temp->prev = lp->head;
	temp->next = lp->head->next;
	lp->head->next = temp;
	temp->next->prev = temp;
	lp->count++;
}

//Adds elt to end of list
// O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));
	temp->data = item; 
	temp->next = lp->head;
	temp->prev = lp->head->prev;
	lp->head->prev = temp;
	temp->prev->next = temp;
	lp->count++;
}

//Removes last elt
// O(1)
void *removeFirst(LIST *lp)
{
	assert(lp != NULL); 
	NODE *pDel = lp->head->next;
	void *first = pDel->data;
	lp->head->next = pDel->next;
	pDel->next->prev = lp->head;
	free(pDel);
	lp->count--;
	return first; 
}

//Removes last elt
// O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL); 
	NODE *pDel = lp->head->prev;
	void *last = pDel->data;
	pDel->prev->next = lp->head;
	lp->head->prev = pDel->prev;
	free(pDel);
	lp->count--;
	return last; 
}

//Returns first elt data
// O(1)
void *getFirst(LIST *lp)
{
	assert(lp != NULL); 
    	return(lp->head->next->data);
}

//Returns last elt data
// O(1)
void *getLast(LIST *lp)
{
	assert(lp != NULL); 
    	return(lp->head->prev->data);
}

//Removes item if it exits
// O(n)
void removeItem(LIST *lp, void *item)
{
	assert(lp->compare != NULL);
	NODE *check = lp->head->next;
	int i;
	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(item, check->data) == 0)
		{
			check->next->prev = check->prev;
		    	check->prev->next = check->next;
		    	free(check);
			lp->count--;
		}
		check = check->next; 	
	}
}

//Returns item data if in array
// O(n)
void *findItem(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *p = lp->head->next;
	int i;
	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(item, p->data) == 0)
		{
	    		return (p->data);
		}
		p = p->next;
	}
	return NULL; 
}

//Returns copy of Items
// O(n)
void *getItems(LIST *lp)
{
	void **copy = malloc(sizeof(void *)*lp->count);
	NODE *p = lp->head->next;
	int i;
	for(i = 0; i < lp->count; i++)
	{
		copy[i] = p->data;
		p = p->next;
	}
	return copy; 
}