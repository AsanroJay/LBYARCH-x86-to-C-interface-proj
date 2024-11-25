void scalarmul_c(int n, float* arr1, float* arr2, float* result) {
    *result = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        *result += (float)(arr1[i] * arr2[i]);
    }
}
