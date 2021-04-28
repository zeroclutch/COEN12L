# include "set.h"
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <stdlib.h>
# include <stdbool.h>
# define EMPTY 0
# define FILLED 1
# define DELETED 2

typedef struct set {
    int count;
    int length;
    void** elements;
    int* flags;
    int (*compare)();
    unsigned (*hash)();
} SET;

/** STATIC FUNCTIONS **/

static int search(SET *sp, void *elt, bool *found);

int search(SET *sp, void *elt, bool *found) {
    unsigned hash = (*sp->hash)(elt);
    int index = -1;
    *found = false;

    // Linear probing
    unsigned key;
    for(int i = 0; i < sp->length; i++) {
        key = (hash + i) % sp->length;
        int flag = sp->flags[key];
        if(flag == FILLED && (*sp->compare)(elt, sp->elements[key]) == 0) {
            *found = true;
            return key;
        } else if(flag == DELETED) {
            index = key;
        } else if(flag == EMPTY) {
            return key;
        }

        key++;
    } while(key != hash % sp->length);

    return index;
}

/** INTERFACE FUNCTIONS **/

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    // Only allow for positively-sized elements
    assert(maxElts > -1);

    // Write to allocated memory
    SET *sp;
    sp = (SET*) malloc(sizeof(SET));

    // Check if memory was allocated
    assert(sp != NULL);

    sp->count    = 0;
    sp->length   = maxElts;
    sp->compare = compare;
    sp->hash = hash;
    sp->elements = malloc(sizeof(void*) * maxElts);
    sp->flags    = malloc(sizeof(void*) * maxElts);

    for(int i = 0; i < maxElts; i++) {
        sp->flags[i] = EMPTY;
    }


    // Check if memory was allocated
    assert(sp->elements != NULL);
    assert(sp->flags != NULL);

    return sp;
}

void destroySet(SET *sp) {
    // Check if set exists
    assert(sp != NULL);

	for(int i = 0; i < sp->count; i++) {
        if(sp->flags[i] == FILLED)
		    free(sp->elements[i]);
    }
    
    // Free all elements and members
    free(sp->flags);
    free(sp->elements);
    free(sp);
}

int numElements(SET *sp) {
    // Check if set exists
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);

    int index;
    bool found = false;

    // Find index
    index = search(sp, elt, &found);

    // Insert if table isn't full and item isn't found
    if(index != -1 && found == false) {
        sp->elements[index] = strdup(elt);
        assert(sp->elements[index] != NULL);
        sp->flags[index] = FILLED;
        sp->count++;
    }

}

void removeElement(SET *sp, void *elt) {
    unsigned hash = (*sp->hash)(elt);
    int element = sp->flags[hash % sp->length];
    if(element == FILLED) {
        sp->flags[hash % sp->length] = DELETED;
        free(sp->elements[hash % sp->length]);
        sp->count--;
    }
}

void *findElement(SET *sp, void *elt) {
    bool found = false;
    int index = search(sp, elt, &found);
    if(found) {
        return sp->elements[index];
    }
    return NULL;
}

void **getElements(SET *sp) {
    // Check if arguments exist
    assert(sp != NULL);

    size_t size = sizeof(void*) * sp->count;
    void **elements = (void**) malloc(size);

    // Only copy filled elements since we don't return flags
    int j = 0;
    for(int i = 0; i < sp->length; i++) {
        if(sp->flags[i] == FILLED) {
            elements[j++] = sp->elements[i];
        }
    }
    
    return elements;
}
