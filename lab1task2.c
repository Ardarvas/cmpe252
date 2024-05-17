#include <stdio.h>
#include <stdlib.h>


void readInput(int **arr, int *nPtr);
void printNumbers(const int arr[], int n);
int compareTwoArrays(const int arr1[], const int arr2[], int n1, int n2);
int calculateAverage(const int arr[], int n);


int main() {
    int *arr1 = NULL, *arr2 = NULL;  
    int n1, n2;

    
    readInput(&arr1, &n1);
    printNumbers(arr1, n1);

  
    readInput(&arr2, &n2);
    printNumbers(arr2, n2);


    int comparisonResult = compareTwoArrays(arr1, arr2, n1, n2);
    switch (comparisonResult) {
        case 0:
            printf("\nEqual\n");
            break;
        case 1:
            printf("\nGreater than\n");
            break;
        case -1:
            printf("\nLess than\n");
            break;
    }

    
    int avg1 = calculateAverage(arr1, n1);
    int avg2 = calculateAverage(arr2, n2);
    printf("\nAverage of the first array: %d\n", avg1);
    printf("Average of the second array: %d\n", avg2);

    
    free(arr1);
    free(arr2);

    return 0;
}


void readInput(int **arr, int *nPtr) {
    printf("Enter the number of elements:\n");
    scanf("%d", nPtr);

  
    *arr = (int *)malloc(*nPtr * sizeof(int));
    if (*arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    printf("Enter %d elements:\n", *nPtr);
    for (int i = 0; i < *nPtr; i++) {
        scanf("%d", &(*arr)[i]);
    }
}


void printNumbers(const int arr[], int n) {
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int compareTwoArrays(const int arr1[], const int arr2[], int n1, int n2) {
    int min_n = (n1 < n2) ? n1 : n2;

    for (int i = 0; i < min_n; i++) {
        if (arr1[i] > arr2[i]) return 1;
        if (arr1[i] < arr2[i]) return -1;
    }

    if (n1 == n2) return 0;
    return (n1 > n2) ? 1 : -1;
}


int calculateAverage(const int arr[], int n) {
    if (n == 0) {
        return 0;  
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}
