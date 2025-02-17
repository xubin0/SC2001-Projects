#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variable to keep track of comparisons
long long comparisonCount = 0;

// Function: Insertion Sort
void insertionSort(int A[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= left && (++comparisonCount && A[j] > key)) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void merge(int A[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    // Merge the temp arrays back into A[left..right]
    int i = 0;  // index for L
    int j = 0;  // index for R
    int k = left; // index for A

    while (i < n1 && j < n2) {
        comparisonCount++;
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) {
        A[k++] = L[i++];
    }
    while (j < n2) {
        A[k++] = R[j++];
    }

    free(L);
    free(R);
}

void hybridMergeSort(int A[], int left, int right, int S) {
    if (left < right) {
        if ((right - left + 1) <= S) {
            insertionSort(A, left, right);
        } else {
            int mid = (left + right) / 2;
            hybridMergeSort(A, left, mid, S);
            hybridMergeSort(A, mid + 1, right, S);
            merge(A, left, mid, right);
        }
    }
}

int main(int argc, char *argv[]) {
    // Example usage:
    //   ./hybrid_merge_sort <n> <S> <x>
    // Where:
    //   n = size of array
    //   S = threshold for insertion sort
    //   x = max random value
    // If not provided, use default values.

    int n = 10000;    // default array size
    int S = 100;       // default threshold
    int x = 100000;   // default max random value

    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) S = atoi(argv[2]);
    if (argc > 3) x = atoi(argv[3]);

    // Allocate memory for array
    int *A = (int *)malloc(n * sizeof(int));
    if (!A) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Seed random number generator and fill array
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = (rand() % x) + 1; 
    }

    // Reset global comparison counter
    comparisonCount = 0;

    // Perform the hybrid merge sort
    hybridMergeSort(A, 0, n - 1, S);

    // Print results
    // For large n, you might not want to print all elements.
    // Here we print only the first 20 for verification.
    printf("First up to 20 elements of the sorted array:\n");
    for (int i = 0; i < n && i < 20; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    // Print number of comparisons
    printf("Number of key comparisons: %lld\n", comparisonCount);

    free(A);
    return 0;
}