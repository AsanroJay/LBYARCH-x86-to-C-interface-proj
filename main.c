#include <stdio.h>
#include <stdlib.h>

#include "kernel.c"

extern void scalarmul(int n, int* arr1, int* arr2, float* ptr);

int main() {
    int n = 5; // Length of vectors

 
    int vec1[] = {1, 2, 3, 4,5};
    int vec2[] = {1, 2, 3, 4,5};
    float vec3[20] = {0.0}; // Array to store multiple results (if needed)
    float var3 = 0;
    float* ptr = &var3; // Pointer to store the result of 1 dot product between vec1 and vec2


    printf("Vector A: %d, %d, %d, %d\n", vec1[0], vec1[1], vec1[2], vec1[3]);
    printf("Vector B: %d, %d, %d, %d\n", vec2[0], vec2[1], vec2[2], vec2[3]);

    int choice = 0;
    int i = 0;

    do {
        printf("\nC [1]  |  x86 assembly [2]  | Exit [3]\nEnter choice: ");
        scanf("%d", &choice); 

        switch (choice) {
            case 1: // Call C kernel
                printf("\nCalling C kernel...\n");
                scalarmul(n, vec1, vec2, ptr);  // C kernel call
                printf("Result from C kernel: %.2f\n", *ptr);
                break;

            case 2: // Call x86 assembly kernel
                printf("\nCalling x86 assembly kernel...\n");
                scalarmul(n, vec1, vec2, ptr);  // Assembly kernel call
                printf("Result from assembly kernel: %.2f\n", *ptr);
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
