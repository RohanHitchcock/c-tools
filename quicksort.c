#include <stdlib.h>

void quicksort(int A[], int n);
void int_swap(int *p1, int *p2);
static void partition(int A[], int n, int p, int *f_eq, int *f_gr);

/*swaps the values of two integer memory locations*/
void int_swap(int *p1, int *p2) {
  int temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}



void
quicksort(int A[], int n) {
    int fe, fg, pivot;

    /*array of length 1 is sorted*/
    if (n <= 1) {
        return;
    } else {
        /*srand() is assumed to already have been called*/
        pivot = A[rand() % n];
        partition(A, n, pivot, &fe, &fg);
        quicksort(A, fe);
        quicksort(A+fg, n-fg);
    }
}

static void
partition(int A[], int n, int p, int *f_eq, int *f_gr) {
    int next=0, fe=0, fg=n;

    while (next < fg) {
        /*if the next item is less than the pivot it goes to A[fe]*/
        if (A[next] < p) {
            int_swap(A+fe, A+next);
            /*first equal goes up by 1 to exclude swapped item*/
            fe++; next++;
        /*if next item is greater than the pivot goes to A[fg - 1]*/
        } else if (A[next] > p) {
            int_swap(A+next, A+fg-1);
            /*fg decreses to include swapped item, next does not increase as a
            new item is at A[next]*/
            fg--;
        } else {
            /*if equal then just extent the equal-to section by 1*/
            next++;
        }
    }

    *f_eq = fe;
    *f_gr = fg;
}
