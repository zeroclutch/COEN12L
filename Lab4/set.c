#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"
#include "list.h"


typedef struct node {
    void* data;
    struct node* next;
    struct node* prev;
}
NODE;

typedef struct list {
    int count;
    struct node* head;
    int(* compare)();
}
LIST;

typedef struct set {
    int length;
    int count;
    int(* compare)();
    unsigned(* hash)();
    LIST*  lists;
}
SET;


/**
 * Creates a new set - O(n) complexity
 */
SET* createSet(int maxElts, int(* compare)(), unsigned(* hash)()) {
    int i;
    SET* sp;
    assert(compare != NULL && hash != NULL);
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts / AVG;
    sp->lists = malloc(sizeof(LIST*) * sp->length);
    for (i = 0; i < sp->length; i++) {
        sp->lists[i] = createList(compare);
    }
    return sp;
}

/**
 * Destroys a set - O(1) complexity
 */
void destroySet(SET* sp) {
    assert(sp != NULL);
    free(sp->lists);
    free(sp);
}

/**
 * Returns number of elements in a set - O(1) complexity
 */
int numElements(SET* sp) {
    assert(sp != NULL);
    return sp->count;
}

/**
 * Adds element to list - O(n) complexity
 */
void addElement(SET* sp, void* elt) {
    assert(sp != NULL && elt != NULL);
    int index = (* sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[index], elt) == NULL) {
        addFirst(sp->lists[index], elt);
        sp->count++;
    }
}

/**
 * Removes an element - O(n) complexity
 */
void removeElement(SET* sp, void* elt) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[index], elt) != NULL) {
        removeItem(sp->lists[index], elt);
        sp->count--;
    }
}


/**
 * Finds an element if it exists - O(n) complexity
 */
void* findElement(SET* sp, void* elt) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[index], elt);
}

/**
 * Copies elements - O(n) complexity
 */
void* getElements(SET* sp) {
    assert(sp != NULL);
    NODE* np;
    void* copy = malloc(sizeof(void* )* sp->count);
    int i, j;
    j = 0;
    for (i = 0; i < sp->length; i++) {
        int count = numItems(sp->lists[i]);
        if (count > 0) {
            np = sp->lists[i]->head->next;
            while (np != sp->lists[i]->head) {
                copy[j] = np->data;
                count++;
                j++;
                np = np->next;
            }
        }
    }
    return copy;
}