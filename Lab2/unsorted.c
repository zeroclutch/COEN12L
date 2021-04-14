// implement a set using an unsorted array of length m>0, in which the first n≤m slots are used to holdnstrings in some arbitrary order. Usesequential search to locate an element in the array. 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "set.h"
# define DEBUG_MODE 1

static int search(SET *sp, char *elt);

typedef struct set {
    int length;
    int max;
    char ** elements;
} SET;

// Constructor
SET *createSet(int maxElts) {
    // Only allow for positively-sized elements
    assert(maxElts > -1);

    // Write to allocated memory
    SET *sp;
    sp = (SET*) malloc(sizeof(SET));

    // Check if memory was allocated
    assert(sp != NULL);

    sp->length = 0;
    sp->max = maxElts;
    sp->elements = malloc(sizeof(char*) * maxElts);
    return sp;
}

void printSet(SET *sp) {
    int i;
    printf("[");
    for(int i = 0; i < sp->length; i++) {
        if(sp->elements[i] != NULL) {
            printf("%s", sp->elements[i]);
        } else {
            printf("NULL");
        }
        if(sp->length - 1 != i) {
            printf(",");
        }
    }
    printf("]");
    printf("\n");
}

// Destroys a set
void destroySet(SET *sp) {
    // Check if set exists
    assert(sp != NULL);

	for(int i = 0; i < sp->length; i++) {
		free(sp->elements[i]);
    }
    
    // Free all elements and members
    free(sp->elements);
    free(sp);
}

int numElements(SET *sp) {
    // Check if set exists
    assert(sp != NULL);

    return sp->length;
}

void addElement(SET *sp, char *elt) {
    // Check if arguments exist
    assert(sp != NULL && elt != NULL);

    // Check if list is full
    assert(sp->max > sp->length);

    char *eltCopy = strdup(elt);
    assert(elt != NULL);

    // Avoid inserting duplicates
    int index = search(sp, elt);
    if(index == -1) {
        sp->elements[sp->length] = eltCopy;
        sp->length++;
    }
}

void removeElement(SET *sp, char *elt) {
    // Check if arguments exist
    assert(sp != NULL && elt != NULL);


    if(sp->length > 0) {
        int index = search(sp, elt);
        if(index > -1) {
            // Replace with last element (arbitrary order)
            sp->elements[index] = sp->elements[sp->length - 1];
            // Set last element to NULL
            sp->elements[sp->length - 1] = NULL;
            sp->length--;
        }
    }
}

char *findElement(SET *sp, char *elt) {
    // Check if arguments exist
    assert(sp != NULL && elt != NULL);

    int index = search(sp, elt);
    if(index > -1) {
        return sp->elements[index];
    } else {
        return NULL;
    }
}

char **getElements(SET *sp) {
    // Check if arguments exist
    assert(sp != NULL);

    char **elements;
    elements = malloc(sizeof(sp->elements));
    
    int i;
    for(i = 0; i < sp->length; i++) {
        elements[i] = sp->elements[i];
    }
    return elements;
}

static int search(SET *sp, char *elt) {
    // Check if arguments exist
    assert(sp != NULL && elt != NULL);
    int i;
    for(int i = 0; i < sp->length; i++) {
        if(strcmp(elt, sp->elements[i]) == 0) {
            return i;
        }
    }
    return -1;
}