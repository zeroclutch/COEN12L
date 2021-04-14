# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

#define MAX_SIZE 1000


int main(int argc, char *argv[]) {
    SET *testSet = createSet(1000);
    char *str1 = "hip";
    char *str2 = "hop";
    char *str3 = "hippy";
    addElement(testSet, str1);
    addElement(testSet, str2);
    addElement(testSet, str3);
    removeElement(testSet, str3);
    //printSet(testSet);
    printf("I am %d elements long\n", numElements(testSet));
    destroySet(testSet);
}