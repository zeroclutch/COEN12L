# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

#define MAX_SIZE 1000

int main(int argc, char *argv[]) {
    SET *testSet = createSet(MAX_SIZE);
    char *str1 = "hip";
    char *str2 = "hop";
    char *str3 = "hippy";
    printf("adding hip\n");
    addElement(testSet, str1);
    printf("adding\n");
    addElement(testSet, str2);
    printf("adding\n");
    addElement(testSet, str3);
    printf("removing\n");
    removeElement(testSet, str3);
    printf("counting\n");
    //printSet(testSet);
    printf("I am %d elements long\n", numElements(testSet));
    printf("destroying\n");
    destroySet(testSet);
}