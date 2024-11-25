#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kernel.c"

extern void scalarmul(int n, float* arr1, float* arr2, float* ptr);

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + (ts.tv_nsec / 1e9);
}

int main() {
    int n = 0;
    int choice = 0;
    int loops = 0;
    int i = 0;
    double start, end, endtotal;
    float var3 = 0;
    float* ptr = &var3; // Pointer to store the result of 1 dot product between vec1 and vec2
    float* vec1 = NULL;
    float* vec2 = NULL;

    do {
        printf("\nEnter size of vectors: ");
        scanf("%d", &n);

        vec1 = (float*)malloc(n * sizeof(float));
        vec2 = (float*)malloc(n * sizeof(float));

        srand(time(NULL));

        for (int i = 0; i < n; i++) {
            vec1[i] = ((float)rand() / RAND_MAX) * 10.0;
            vec2[i] = ((float)rand() / RAND_MAX) * 10.0;
        }

        // printf("\nVector A: ");
        // for (int i = 0; i < n; i++) {
        //     printf("%.2f ", vec1[i]);
        // }
        // printf("\n");

        // printf("Vector B: ");
        // for (int i = 0; i < n; i++) {
        //     printf("%.2f ", vec2[i]);
        // }

        do {
            // Step 2: Ask for kernel choice
            printf("\n[1] C\n[2] x86 assembly\n[3] Exit\nEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 3) {
                printf("Exited.\n");
                break;
            }

            // Step 3: Ask for number of loops
            printf("\nEnter amount of loops: ");
            scanf("%d", &loops);

            endtotal = 0;

            for (i = 0; i < loops; i++) {
                if (choice == 1) {
                    // C kernel
                    printf("\n%d) Calling C kernel...\n", i);
                    start = get_time_in_seconds();
                    scalarmul_c(n, vec1, vec2, ptr);  // C kernel call
                    end = get_time_in_seconds();
                    end = end - start;
                    endtotal += end;
                    printf("Result from C kernel: %.2f\n", *ptr);
                    printf("Time taken (C kernel): %.8f seconds\n", end);
                } else if (choice == 2) {
                    // Assembly kernel
                    printf("\n%d) Calling x86 assembly kernel...\n", i);
                    start = get_time_in_seconds();
                    scalarmul(n, vec1, vec2, ptr);  // Assembly kernel call
                    end = get_time_in_seconds();
                    end = end - start;
                    endtotal += end;
                    printf("Result from assembly kernel: %.2f\n", *ptr);
                    printf("Time taken (Assembly kernel): %.8f seconds\n", end);
                } else {
                    printf("Invalid kernel choice. Please select again.\n");
                    break;
                }
            }

            if (choice == 1 || choice == 2) {
                printf("\nAverage execution time for %d loops: %.8f seconds\n", loops, endtotal / loops);
            }

            printf("\n\n[1] Try another kernel with the same vector size\n[2] Choose a new vector size\n[3] Exit\nEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 2) {
                free(vec1);
                free(vec2);
                break; 
            } else if (choice == 3) {
                printf("Exited.\n");
                free(vec1);
                free(vec2);
                return 0; 
            }

        } while (choice == 1); // Loop back to kernel choice

    } while (choice == 2); // Loop back to vector size

    free(vec1);
    free(vec2);

    return 0;
}
