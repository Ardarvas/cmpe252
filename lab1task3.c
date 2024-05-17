#include <stdio.h>
#define SIZE 500

// Function prototypes
void readInput(int arr[], int *nPtr);
void printNumbers(const int arr[], int n);
void circularShiftFromLeftToRight(int arr[], int n);
int compareTwoArrays(const int arr1[], const int arr2[], int n1, int n2);
void circularShiftUntilMinArr(int arr[], int n);
int findMax(const int arr[], int n);


int main() {
    int arr[SIZE];
    int n;

   
    readInput(arr, &n);
    printf("Array elements: ");
    printNumbers(arr, n);

   
    circularShiftUntilMinArr(arr, n);
    printf("\nAfter circularShiftUntilMinArr:\nArray elements: ");
    printNumbers(arr, n);

   
    int maxElement = findMax(arr, n);
    printf("Maximum element of the array: %d\n", maxElement);

    return 0;
}


void readInput(int arr[], int *nPtr) {
    printf("Enter the number of elements:\n");
    scanf("%d", nPtr);
    printf("Enter %d elements:\n", *nPtr);
    for (int i = 0; i < *nPtr; i++) {
        scanf("%d", &arr[i]);
    }
}


void printNumbers(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



void circularShiftFromLeftToRight(int arr[], int n) {
    if (n <= 1) return;

    int last = arr[n - 1];
    for (int i = n - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}


int compareTwoArrays(const int arr1[], const int arr2[], int n1, int n2) {
    int minLen = (n1 < n2) ? n1 : n2;

    for (int i = 0; i < minLen; i++) {
        if (arr1[i] > arr2[i]) return 1;
        if (arr1[i] < arr2[i]) return -1;
    }

    return (n1 == n2) ? 0 : ((n1 > n2) ? 1 : -1);
}


void circularShiftUntilMinArr(int arr[], int n) {
    int tempArr[SIZE];
    int minArr[SIZE];


    for (int i = 0; i < n; i++) {
        minArr[i] = arr[i];
    }

 
    for (int shift = 0; shift < n; shift++) {
        for (int i = 0; i < n; i++) {
            tempArr[i] = arr[(i + shift) % n];
        }

        if (compareTwoArrays(tempArr, minArr, n, n) < 0) {
            for (int i = 0; i < n; i++) {
                minArr[i] = tempArr[i];
            }
        }
    }


    for (int i = 0; i < n; i++) {
        arr[i] = minArr[i];
    }
}


int findMax(const int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
