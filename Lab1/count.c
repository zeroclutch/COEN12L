# include <stdio.h>
# include <string.h>
# define MAX_WORD_LENGTH 30

int main(int argc, char* argv[]) {

    char* COUNTING_FILE = argv[1];
    FILE* file = fopen(COUNTING_FILE, "r");

    if(file == NULL) {
        printf("Error: Invalid file!\n");
    } else {
        int count = 0;
        char name[MAX_WORD_LENGTH];

        while(!feof(file)) {
            fscanf(file, "%s", &name);
            count++;
        }
        printf("%d total words", count);
    }
    fclose(file);
}