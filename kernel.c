void scalarmul(int n, int* arr1, int* arr2, float* result) {
    *result = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        *result += (float)(arr1[i] * arr2[i]);
    }
}
