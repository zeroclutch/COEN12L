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
    char** elements;
    int* flags;
} SET;

/** STATIC FUNCTIONS **/

static unsigned strhash(char *s);
static int search(SET *sp, char *elt, bool *found);

unsigned strhash(char *s) {
    unsigned hash = 0;
    while (*s != '\0') {
        hash = 31 * hash + *s ++;
    }
    return hash;
}

int search(SET *sp, char *elt, bool *found) {
    unsigned hash = strhash(elt);
    int index = -1;
    *found = false;

    // Linear probing
    unsigned key;
    for(int i = 0; i < sp->length; i++) {
        key = (hash + i) % sp->length;
        int flag = sp->flags[key];
        if(flag == FILLED && strcmp(elt, sp->elements[key]) == 0) {
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

SET *createSet(int maxElts) {
    // Only allow for positively-sized elements
    assert(maxElts > -1);

    // Write to allocated memory
    SET *sp;
    sp = (SET*) malloc(sizeof(SET));

    // Check if memory was allocated
    assert(sp != NULL);

    sp->count    = 0;
    sp->length   = maxElts;
    sp->elements = malloc(sizeof(char*) * maxElts);
    sp->flags    = malloc(sizeof(char*) * maxElts);

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

void addElement(SET *sp, char *elt) {
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

void removeElement(SET *sp, char *elt) {
    assert(sp != NULL && elt != NULL);
    bool found = false;
    int index = search(sp, elt, &found);
    if(found) {
        assert(sp->elements[index] != NULL);
        sp->flags[index] = DELETED;
        sp->count--;
    }
}

char *findElement(SET *sp, char *elt) {
    bool found = false;
    int index = search(sp, elt, &found);
    if(found) {
        return sp->elements[index];
    }
    return NULL;
}

char **getElements(SET *sp) {
    // Check if arguments exist
    assert(sp != NULL);

    size_t size = sizeof(char*) * sp->count;
    char **elements = (char**) malloc(size);

    // Only copy filled elements since we don't return flags
    int j = 0;
    for(int i = 0; i < sp->length; i++) {
        if(sp->flags[i] == FILLED) {
            elements[j++] = sp->elements[i];
        }
    }
    
    return elements;
}
