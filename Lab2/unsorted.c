// implement a set using an unsorted array of length m>0, in which the first n≤m slots are used to holdnstrings in some arbitrary order. Usesequential search to locate an element in the array. 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "set.h"
# define DEBUG_MODE 1

static int search(SET *sp, char *elt);

/**
 * @brief A collection of strings
 * int length The number of elements currently in the set
 * int max The maximum size of the set
 * char** elements An array of the strings
 */
typedef struct set {
    int length;
    int max;
    char ** elements;
} SET;

/**
 * @brief Creates a new set and returns its pointer
 * 
 * Runtime: O(1)
 * 
 * int maxElts The maximum number of elements the set can hold
 */
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

/**
 * @brief Prints the set
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 */
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

/**
 * @brief Destroys the set
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 */
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

/**
 * @brief Returns the set length
 * 
 * Runtime: O(1)
 * 
 * SET *sp The set pointer this refers to
 */
int numElements(SET *sp) {
    // Check if set exists
    assert(sp != NULL);

    return sp->length;
}

/**
 * @brief Adds an element to the set in order
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 * char *elt The element to add
 */
void addElement(SET *sp, char *elt) {
    // Check if arguments exist
    assert(sp != NULL && elt != NULL);

    // Check if list is full
    assert(sp->max > sp->length);

    char *eltCopy = strdup(elt);
    assert(eltCopy != NULL);

    // Avoid inserting duplicates
    int index = search(sp, elt);
    if(index == -1) {
        sp->elements[sp->length] = eltCopy;
        sp->length++;
    }
}

/**
 * @brief Removes an element from the set
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 * char *elt The element to remove
 */
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

/**
 * @brief Finds an element in a set and returns the element if found
 * if not, then it returns NULL.
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 * char *elt The string to find
 */
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

/**
 * @brief Moves the elements to a new set
 * 
 * Runtime: O(n)
 * 
 * SET *sp The set pointer this refers to
 * char *elt The element to remove
 */
char **getElements(SET *sp) {
    // Check if arguments exist
    assert(sp != NULL);

    char **elements = (char*) malloc(sizeof(char*) * sp->length);
    
    elements = sp->elements;
    
    return elements;
}

/**
 * @brief Implements sequential search to find the correct location
 * for an element that has not been inserted into the set.
 * 
 * Runtime: O(n)
 * 
 * @param sp The pointer to the set
 * @param elt The element to insert
 * @return int Returns -1 if there is a match, or the index where
 * the unique element should be inserted.
 */
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
