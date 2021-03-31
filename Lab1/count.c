# include <stdio.h>
# include <string.h>
# define MAX_WORD_LENGTH 30

int main(int argc, char* argv[]) {
    // Accept file as first command line argument
    if(argc < 2) {
        printf("Error: File not found.\n");
        return 1;
    }

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
        printf("%d total words\n", count);
        fclose(file);
    }
}