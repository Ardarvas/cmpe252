#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILE_NAME "library.bin"

typedef struct {
    int id; // book id
    char name[20]; // book name
    char author[20]; // author of book
    int quantity; // quantity of book
    int rackno; // rack no of the book
} bookData;

// Function Declarations
void showRecords();
int updateRecord(int id, int diff);
int deleteRecord(int id);
void mainMenu();


int main() {
    mainMenu();
    return 0;
}


void mainMenu() {
    int id, diff;

    printf("\nBooks:\n");
    showRecords();

    printf("\nEnter id of the book to be updated:\n");
    scanf("%d", &id);
    printf("\nHow many books will be added(+) or removed(-):\n");
    scanf("%d", &diff);

    if (updateRecord(id, diff) == 0)
        printf("There is no book with id %d\n", id);

    printf("\nBooks:\n");
    showRecords();

    printf("\nEnter id of the book to be deleted:\n");
    scanf("%d", &id);

    if (deleteRecord(id) == 0)
        printf("There is no book with id %d\n", id);

    printf("\nBooks:\n");
    showRecords();
}


void showRecords() {
    FILE *file = fopen(FILE_NAME, "rb");
    bookData book;

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&book, sizeof(bookData), 1, file)) {
        if (book.id != 0) { 
            printf("id: %d\nname: %s\nauthor: %s\nquantity: %d\nrackno: %d\n\n",
                   book.id, book.name, book.author, book.quantity, book.rackno);
        }
    }
    fclose(file);
}

int updateRecord(int id, int diff) {
    FILE *file = fopen(FILE_NAME, "rb+");
    bookData book;
    int found = 0;

    if (!file) {
        printf("Error opening file\n");
        return 0;
    }

    while (fread(&book, sizeof(bookData), 1, file) && !found) {
        if (book.id == id) {
            fseek(file, -sizeof(bookData), SEEK_CUR);
            book.quantity += diff;
            fwrite(&book, sizeof(bookData), 1, file);
            found = 1;
        }
    }
    fclose(file);
    return found;
}


int deleteRecord(int id) {
    FILE *file = fopen(FILE_NAME, "rb+");
    bookData book;
    int found = 0;

    if (!file) {
        printf("Error opening file\n");
        return 0;
    }

    while (fread(&book, sizeof(bookData), 1, file) && !found) {
        if (book.id == id) {
            fseek(file, -sizeof(bookData), SEEK_CUR);
            memset(&book, 0, sizeof(bookData)); //        RESET ATIO
            fwrite(&book, sizeof(bookData), 1, file);
            found = 1;
        }
    }
    fclose(file);
    return found;
}
