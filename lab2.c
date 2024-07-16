#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_ELEM 10
#define STR_LEN 100

unsigned int hash_text(char *list);
void strong_similar(int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]);
void weak_similar(char list[MAX_ELEM][STR_LEN], int map[MAX_ELEM][MAX_ELEM]);
void print_string_lengths(char list[MAX_ELEM][STR_LEN]);
void print_hash_and_similarities(char list[MAX_ELEM][STR_LEN], int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]);
void print_weak_similarities(char list[MAX_ELEM][STR_LEN], int map[MAX_ELEM][MAX_ELEM]);

int main() {
    
    char list[MAX_ELEM][STR_LEN];
    int hashed_vals[MAX_ELEM];
    int same[MAX_ELEM][MAX_ELEM] = {0};
    int weak_same[MAX_ELEM][MAX_ELEM] = {0};

    printf("Enter 10 elements:\n \n");

    
    for (int i = 0; i < MAX_ELEM; i++) {
        fgets(list[i], STR_LEN, stdin);
        list[i][strcspn(list[i], "\n")] = 0;  
    }

    for (int i = 0; i < MAX_ELEM; i++) {
        hashed_vals[i] = hash_text(list[i]);
    }

    
    strong_similar(hashed_vals, same);

   
    weak_similar(list, weak_same);

    print_hash_and_similarities(list, hashed_vals, same);
    printf("\nElements with weak similarities:\n");
    print_weak_similarities(list, weak_same);
    printf("\nString Lengths Without Spaces:\n");
    print_string_lengths(list);

    return 0;
}

unsigned int hash_text(char *list) {
    unsigned int hash = 0;
    unsigned int p = 36;

   
    while (*list) {
        
        hash = (hash * p + *list) % 1000;
        list++; 
    }

    return hash;
}

void strong_similar(int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]) {
    for (int i = 0; i < MAX_ELEM; i++) {
        for (int j = 0; j < MAX_ELEM; j++) {
            map[i][j] = (hval[i] == hval[j] && i != j) ? 1 : 0;
        }
    }
}

void weak_similar(char list[MAX_ELEM][STR_LEN], int map[MAX_ELEM][MAX_ELEM]) {
    
    char names[MAX_ELEM][2][STR_LEN] = {{{0}}};
    
    int name_hashes[MAX_ELEM] = {0};
    int surname_hashes[MAX_ELEM] = {0};

    
    for (int i = 0; i < MAX_ELEM; i++) {
        char temp[STR_LEN];
        strcpy(temp, list[i]);
        char *name = strtok(temp, " ");
        char *surname = strtok(NULL, " ");

        if (name && surname) {
            strcpy(names[i][0], name);
            strcpy(names[i][1], surname);
            name_hashes[i] = hash_text(names[i][0]);
            surname_hashes[i] = hash_text(names[i][1]);
        }
    }

    for (int i = 0; i < MAX_ELEM; i++) {
        for (int j = 0; j < MAX_ELEM; j++) {
            if (i != j) {
                if (name_hashes[i] == name_hashes[j] || surname_hashes[i] == surname_hashes[j]) {
                    map[i][j] = 1;
                } else {
                    map[i][j] = 0;
                }
            } else {
                map[i][j] = 0; 
            }
        }
    }
}

void print_string_lengths(char list[MAX_ELEM][STR_LEN]) {
    for (int i = 0; i < MAX_ELEM; i++) {
        int count = 0;
        for (int j = 0; j < strlen(list[i]); j++) {
            if (list[i][j] != ' ') {
                count++;
            }
        }
        printf("%s - %d\n", list[i], count);
    }
}

void print_hash_and_similarities(char list[MAX_ELEM][STR_LEN], int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]) {
    printf("Elements with hash values and similarities:\n\n");
    for (int i = 0; i < MAX_ELEM; i++) {
        printf("%-20s %3d", list[i], hval[i]);
        for (int j = 0; j < MAX_ELEM; j++) {
            if (map[i][j] && i != j) {
                printf(" %3d", j);
            }
        }
        printf("\n");
    }
}

void print_weak_similarities(char list[MAX_ELEM][STR_LEN], int map[MAX_ELEM][MAX_ELEM]) {
    for (int i = 0; i < MAX_ELEM; i++) {
        printf("%-20s %3d", list[i], hash_text(list[i]));
        for (int j = 0; j < MAX_ELEM; j++) {
            if (map[i][j] && i != j) {
                printf(" %3d", j);
            }
        }
        printf("\n");
    }
}
