#include <stdlib.h>

static void intswap(int *p1, int *p2);
static void build_heap(int A[], int n);
static void sift_down(int A[], int p, int n);
void heapsort(int A[], int n);


void heapsort(int A[], int n) {
    int i;

    build_heap(A, n);

    /*array is now a heap. remember the biggest element is always at the start
    of a heap*/
    for (i=n-1; i > 0; i--) {
        intswap(A+i, A);

        /*every element swapped needs to be sifted down on. now ignores the
        last element in the array (as it is in place)*/
        sift_down(A, 0, i);
    }
}


static void sift_down(int A[], int p, int n) {
    int child;



    /*children are at 2p+1 and 2p+2*/
    if ((child = 2*p + 1) < n) {

        /*if the other child exists and is bigger*/
        if (child + 1 < n && A[child] < A[child + 1]) {
            child += 1;

        /*child is now the largest of the two children, if it its bigger than
        the parent then swap the two and sift down on the swapped element*/
        }
        
        if (A[p] < A[child]) {
            intswap(A+p, A+child);
            sift_down(A, child, n);
        }

    }
}


static void build_heap(int A[], int n) {
    int i;

    for (i=n/2-1; i>=0; i--) {
        sift_down(A, i, n);
    }
}


/*swaps the values of two integer memory locations*/
void intswap(int *p1, int *p2) {
  int temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
