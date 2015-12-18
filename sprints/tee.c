#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 16
#define MAX_OPEN_FILES 256

int main(int argc, char *argv[]) {
    /*
     * An implementation of tee.c
     * See http://en.wikipedia.org/wiki/Tee_(command)
     */

    if (argc < 2) {
        fprintf(stderr, "too few arguments");
        return 1;
    }
    if (argc-2 > MAX_OPEN_FILES) {
        fprintf(stderr, "too many write streams will be opened");
        return 1;
    }

    FILE *output_files[MAX_OPEN_FILES];
    char somestr[BUFFER_SIZE];

    // set up write file streams for all command line file arguments
    for(int i = 0; i < argc-1; i++)
        output_files[i] = fopen(argv[i+1], "w");

    while(scanf("%s", &somestr) == 1) {
        // write to stdout
        printf("%s\n", somestr);

        // write to every file stream
        for(int i = 0; i < argc-1; i++)
            fprintf(output_files[i], "%s\n", somestr);
    }

    return 0;
}
