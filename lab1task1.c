#include <stdio.h>
#define SIZE 500


void getInput(int arr[], int *num);
void displayArray(const int arr[], int num);
void shiftRightCircular(int arr[], int num);

int main() {
    int elements[SIZE];
    int size;

    getInput(elements, &size);
    printf("Array Elements:");
    displayArray(elements, size);

    shiftRightCircular(elements, size);
    printf("\nAfter one circular shifts from right to left:\nArray elements:");
    displayArray(elements, size);

    return 0;
}

void getInput(int arr[], int *num) {
    printf("Enter the number of elements: \n");
    scanf("%d", num);
    *num = (*num > SIZE) ? SIZE : *num;
    printf("Enter %d elements:\n", *num);

    for (int idx = 0; idx < *num; idx++) {
        scanf("%d", &arr[idx]);
    }
}

void displayArray(const int arr[], int num) {
    for (int idx = 0; idx < num; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
}

void shiftRightCircular(int arr[], int num) {
    if (num > 1) {
        int last = arr[num - 1];
        for (int idx = num - 1; idx > 0; idx--) {
            arr[idx] = arr[idx - 1];
        }
        arr[0] = last;
    }
}
