/*
 * Application to alphabetize a file with words or phrases separated by new
 * line characters
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80
#define MAX_LINES       256

void insertion_sort(int *A, int length);

void insertion_sort(int *A, int length) {
    int temp;
    for (int i = 1; i < length; i++) {
        int j = i;
        while (j > 0 && A[j-1] > A[j]) {
            temp = A[j];
            A[j] = A[j-1];
            A[j-1] = temp;
            j = j - 1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    char total[MAX_LINES][MAX_LINE_LENGTH];

    int i = 0;

    while (i<=MAX_LINES && *total[i] != EOF &&
            (fscanf(in, "%s\n", total[i]) == 1)) {
        i++;
    }

    for (int j = 0; j < i; j++) {
        printf("%s\n", total[j]);
    }

    int arr[] = {5, 4, 3, 2, 1, 6, 7, 9, 11};

    for (int j = 0; j < 9; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    insertion_sort(arr, 9);

    for (int j = 0; j < 9; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    fclose(in);
    fclose(output);

    return 0;
}
