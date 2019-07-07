#include <stdlib.h>

void mergesort(int A[], int n);
static void merge(int *A, int mid, int n);
static void copy_array(int *A, int *A_copy, int n) ;

void mergesort(int A[], int n) {
    int mid;

    /*array of length 1 is sorted*/
    if (n <= 1) {
        return;
    }

    mid = n / 2;
    mergesort(A, mid);
    mergesort(A+mid, n-mid);
    /*each half of the array is sorted*/
    merge(A, mid, n);
}

static void merge(int *A, int mid, int n) {
    int T[n], i=0, s1=0, s2=mid;
    /*copies first half of array into temporary storage as this will be
    overwritten*/
    copy_array(A, T, mid);

    while (s1 < mid && s2 < n) {
        /*puts the smallest element avalible to the start of the array*/
        if (T[s1] < A[s2]) {
            A[i++] = T[s1++];

        } else {
            A[i++] = A[s2++];

        }
        /*copies remainder of temporary array back into A (must be greater) */
        copy_array(T+s1, A+i, mid - s1);

    }
}

static void copy_array(int *A, int *A_copy, int n) {
    int i;

    for (i=0; i<n; i++) {
        A_copy[i] = A[i];
    }

}
