#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SKATERS 20
#define MAX_NAME_LENGTH 21  // Max name length + null terminator
#define MAX_SCORES 6

typedef struct {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    double scores[MAX_SCORES];
    double average;
} Skater;

int compareScores(const void *a, const void *b) {
    double arg1 = *(const double *)a;
    double arg2 = *(const double *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

double calculateAverageScore(const double scores[], size_t size) {
    if (size <= 2) return 0; // Not enough scores to exclude min and max

    double sortedScores[MAX_SCORES];
    memcpy(sortedScores, scores, size * sizeof(double));
    qsort(sortedScores, size, sizeof(double), compareScores);

    double sum = 0;
    for (size_t i = 1; i < size - 1; i++) {
        sum += sortedScores[i];
    }

    return sum / (size - 2);
}

bool scanSkater(FILE *file, Skater *skater) {
    if (fscanf(file, "%20s %20s", skater->name, skater->surname) != 2)
        return false;

    for (int i = 0; i < MAX_SCORES; i++) {
        if (fscanf(file, "%lf", &skater->scores[i]) != 1)
            return false;
    }

    skater->average = calculateAverageScore(skater->scores, MAX_SCORES);
    return true;
}

int loadSkaters(const char *filename, Skater skaters[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s.\n", filename);
        return -1;
    }

    printf("Opening %s\n", filename);

    int count = 0;
    while (count < MAX_SKATERS && scanSkater(file, &skaters[count])) {
        count++;
    }

    printf("Loading complete\nClosing %s\n", filename);
    fclose(file);
    return count;
}

void printSkater(const Skater *skater) {
    printf("%s %s %.2f\n", skater->name, skater->surname, skater->average);
}

int findAndPrintWinner(const Skater skaters[], int count) {
    if (count == 0) {
        fprintf(stderr, "No skaters were loaded.\n");
        return -1;
    }

    int winnerIndex = 0;
    for (int i = 1; i < count; i++) {
        if (skaters[i].average > skaters[winnerIndex].average) {
            winnerIndex = i;
        }
    }

    printf("Winner:\n");
    printSkater(&skaters[winnerIndex]);
    return winnerIndex;
}

int main(void) {
    Skater skaters[MAX_SKATERS];
    char filename[100];

    printf("Enter the file name to read: ");
    scanf("%99s", filename);

    int numOfSkaters = loadSkaters(filename, skaters);
    if (numOfSkaters < 0) return 1;

    printf("Skaters:\n");
    for (int i = 0; i < numOfSkaters; i++) {
        printSkater(&skaters[i]);
    }

    findAndPrintWinner(skaters, numOfSkaters);
    return 0;
}


//
// Mari Solev 4 7 5 6 4 5
// Julya Sone 6 5 6 3 4 6
// Alexand Tatiay 5 4 6 8 4 5 // text file content 
// Joan Jung 6 8 5 3 7 4
// Amy Bell 7 4 5 2 6 4
//  
