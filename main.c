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

    printf("Enter size of vectors: ");
    scanf("%d",&n);

    float* vec1 = (float*)malloc(n * sizeof(float));
    float* vec2 = (float*)malloc(n * sizeof(float));


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
        printf("%.2f ", vec1[i]);
    }
    printf("\n");

    printf("\n\nVector B: ");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", vec2[i]);
    }
    printf("\n");


    int choice = 0;
    int i = 0;
    double start;
    double end;
    int innerchoice = 0;
    double endtotal = 0;
    do {
        printf("\nC [1]  |  x86 assembly [2]  | Exit [3]\nEnter choice: ");
        scanf("%d", &choice); 

        switch (choice) {
            case 1: // Call C kernel
                endtotal = 0;
                printf("Enter amount of loops: ");
                scanf("%d",&innerchoice);

                for(i = 0; i < innerchoice; i++){
                    printf("\nCalling C kernel...\n");
                    start = get_time_in_seconds();
                    scalarmul_c(n, vec1, vec2, ptr);  // C kernel call
                    end = get_time_in_seconds();
                    end = end - start;
                    endtotal += end;
                    printf("Result from C kernel: %.2f\n", *ptr);
                    printf("Time taken (C kernel): %.8f seconds\n", end);
                }

                    printf("\nAverage execution time for %d loops",innerchoice);
                    printf("\nAverage Time taken (C kernel): %.8f seconds\n", endtotal/innerchoice);
                   
                break;

            case 2: // Call x86 assembly kernel
                endtotal = 0;
                printf("Enter amount of loops: ");
                scanf("%d",&innerchoice);

                for(i = 0; i < innerchoice; i++){
                     printf("\nCalling x86 assembly kernel...\n");
                    start = get_time_in_seconds();
                    scalarmul(n, vec1, vec2, ptr);  // Assembly kernel call
                    end = get_time_in_seconds();
                    end = end - start;
                    endtotal += end;
                    printf("Result from assembly kernel: %.2f\n", *ptr);
                    printf("Time taken (Assembly kernel): %.8f seconds\n", end);
                 }
                    
                    printf("\nAverage execution time for %d loops",innerchoice);
                    printf("\nTime taken (Assembly kernel): %.8f seconds\n", endtotal/innerchoice);
                break;

            case 3: // Exit
                printf("Exited.\n");
                break;

            default: 
                printf("Enter a valid choice!\n");
                break;
        }

    } while (choice != 3);  // Repeat until exit

    free(vec1); 
    free(vec2);

    return 0;
}
