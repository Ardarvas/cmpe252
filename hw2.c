#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ATTENDEES 500
#define LINE_LENGTH 1024

typedef struct {
    char firstname[100];
    char lastname[100];
    double total_duration;
    int id; // Field to preserve the original order
} Attendee;

int read_attendees(const char *filename, Attendee attendees[]);
void consolidate_attendees(Attendee attendees[], int *count, int keep_order);
int compare(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);
void print_attendees(const Attendee attendees[], int count, double min_duration);
int is_all_upper(const char *str);

int main() {
    char filename[100];
    double min_duration;
    char sort_option[10];

    scanf("%99s", filename);
    scanf("%lf", &min_duration);
    scanf(" %9s", sort_option);  // Skip whitespace

    Attendee attendees[MAX_ATTENDEES];
    int count = read_attendees(filename, attendees);
    if (count == -1) {
        return 1;  // File reading error
    }

    int keep_order = (strcmp(sort_option, "1") == 0);
    consolidate_attendees(attendees, &count, keep_order);

    if (strcmp(sort_option, "sorted") == 0) {
        qsort(attendees, count, sizeof(Attendee), compare);
    }

    print_attendees(attendees, count, min_duration);
    return 0;
}

int read_attendees(const char *filename, Attendee attendees[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return -1;
    }

    char line[LINE_LENGTH];
    fgets(line, sizeof(line), file);  // Skip the header line

    int count = 0;
    while (fgets(line, sizeof(line), file) && count < MAX_ATTENDEES) {
        char *tokens[5];
        char *token;
        int token_count = 0;

        token = strtok(line, ",");
        while (token != NULL && token_count < 5) {
            tokens[token_count++] = token;
            token = strtok(NULL, ",\n");
        }

        if (token_count < 4) {
            continue;
        }

        double duration = atof(tokens[token_count - 1]); // Last token is the duration
        char *last_space = strrchr(tokens[0], ' ');
        if (last_space) {
            *last_space = '\0';
            strncpy(attendees[count].firstname, tokens[0], sizeof(attendees[count].firstname) - 1);
            strncpy(attendees[count].lastname, last_space + 1, sizeof(attendees[count].lastname) - 1);
        } else {
            strncpy(attendees[count].firstname, "", sizeof(attendees[count].firstname) - 1);
            strncpy(attendees[count].lastname, tokens[0], sizeof(attendees[count].lastname) - 1);
        }

        attendees[count].id = count;  // Assign id based on order of appearance
        attendees[count].total_duration = duration;
        count++;
    }

    fclose(file);
    return count;
}

void consolidate_attendees(Attendee attendees[], int *count, int keep_order) {
    // Sort first to consolidate correctly
    qsort(attendees, *count, sizeof(Attendee), compare);
    int write_index = 0;
    for (int i = 1; i < *count; i++) {
        if (strcasecmp(attendees[write_index].lastname, attendees[i].lastname) == 0 &&
            strcasecmp(attendees[write_index].firstname, attendees[i].firstname) == 0) {
            attendees[write_index].total_duration += attendees[i].total_duration;
        } else {
            attendees[++write_index] = attendees[i];
        }
    }
    *count = write_index + 1;
    if (keep_order) {
        // Re-sort by ID to restore the original order
        qsort(attendees, *count, sizeof(Attendee), compare_by_id);
    }
}

int compare(const void *a, const void *b) {
    const Attendee *att1 = (const Attendee *)a;
    const Attendee *att2 = (const Attendee *)b;
    int last_cmp = strcasecmp(att1->lastname, att2->lastname);
    if (last_cmp != 0) return last_cmp;
    return strcasecmp(att1->firstname, att2->firstname);
}

int compare_by_id(const void *a, const void *b) {
    const Attendee *att1 = (const Attendee *)a;
    const Attendee *att2 = (const Attendee *)b;
    return att1->id - att2->id;
}

void print_attendees(const Attendee attendees[], int count, double min_duration) {
    for (int i = 0; i < count; i++) {
        if (attendees[i].total_duration >= min_duration) {
            printf("%s %s %.2f\n", attendees[i].lastname, attendees[i].firstname, attendees[i].total_duration);
        }
    }
}

int is_all_upper(const char *str) {
    while (*str) {
        if (isalpha((unsigned char)*str) && !isupper((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}
