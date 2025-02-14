#include <stdio.h>
#include <stdlib.h>

int keyComp = 0; // Global comparison counter

// Function to perform Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
            keyComp++;
        }
        arr[j + 1] = key;
    }
}

// Function to merge two halves
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    
    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
        keyComp++;
    }
    
    while (i < leftSize) {
        arr[k++] = left[i++];
    }
    
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

// Function to perform Merge Sort
void mergeSort(int arr[], int n) {
    if (n > 1) {
        int mid = n / 2;
        int *left = (int*) malloc(mid * sizeof(int));
        int *right = (int*) malloc((n - mid) * sizeof(int));
        
        for (int i = 0; i < mid; i++) left[i] = arr[i];
        for (int i = mid; i < n; i++) right[i - mid] = arr[i];
        
        mergeSort(left, mid);
        mergeSort(right, n - mid);
        merge(arr, left, mid, right, n - mid);
        
        free(left);
        free(right);
    }
}

// Function to perform Hybrid Sort
void hybridSort(int arr[], int n, int S) {
    if (n > 1) {
        if (n <= S) {
            insertionSort(arr, n);
        } else {
            int mid = n / 2;
            int *left = (int*) malloc(mid * sizeof(int));
            int *right = (int*) malloc((n - mid) * sizeof(int));
            
            for (int i = 0; i < mid; i++) left[i] = arr[i];
            for (int i = mid; i < n; i++) right[i - mid] = arr[i];
            
            hybridSort(left, mid, S);
            hybridSort(right, n - mid, S);
            merge(arr, left, mid, right, n - mid);
            
            free(left);
            free(right);
        }
    }
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function for testing
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int S = 3; // Threshold for hybrid sort
    
    printf("Original array: ");
    printArray(arr, n);
    
    hybridSort(arr, n, S);
    
    printf("Sorted array: ");
    printArray(arr, n);
    printf("Key comparisons: %d\n", keyComp);
    
    return 0;
}