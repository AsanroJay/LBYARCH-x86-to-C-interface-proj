#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kernel.c"

extern void scalarmul(int n, int* arr1, int* arr2, float* ptr);

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + (ts.tv_nsec / 1e9);
}

int main() {
    int n = 5; // Length of vectors

    int vec1[n];
    int vec2[n];

    float var3 = 0;
    float* ptr = &var3; // Pointer to store the result of 1 dot product between vec1 and vec2

    srand(time(NULL));

    // Initialize vectors with random values between 0 and 9
    for (int i = 0; i < n; i++) {
        vec1[i] = rand() % 10;
        vec2[i] = rand() % 10;
    }

    // Print the randomized vectors
    printf("Vector A: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vec1[i]);
    }
    printf("\n");

    printf("Vector B: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", vec2[i]);
    }
    printf("\n");


    int choice = 0;
    int i = 0;
    double start;
    double end;

    do {
        printf("\nC [1]  |  x86 assembly [2]  | Exit [3]\nEnter choice: ");
        scanf("%d", &choice); 

        switch (choice) {
            case 1: // Call C kernel
                start = get_time_in_seconds();
                printf("\nCalling C kernel...\n");
                scalarmul_c(n, vec1, vec2, ptr);  // C kernel call
                end = get_time_in_seconds();
                printf("Result from C kernel: %.2f\n", *ptr);
                printf("Time taken (C kernel): %.6f seconds\n", end - start);
                break;

            case 2: // Call x86 assembly kernel
                start = get_time_in_seconds();
                printf("\nCalling x86 assembly kernel...\n");
                scalarmul(n, vec1, vec2, ptr);  // Assembly kernel call
                end = get_time_in_seconds();
                printf("Result from assembly kernel: %.2f\n", *ptr);
                printf("Time taken (Assembly kernel): %.6f seconds\n", end - start);
                break;

            case 3: // Exit
                printf("Exited.\n");
                break;

            default: 
                printf("Enter a valid choice!\n");
                break;
        }

    } while (choice != 3);  // Repeat until exit

    return 0;
}
