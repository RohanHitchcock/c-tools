/*swaps the values of two integer memory locations*/
void intswap(int *p1, int *p2) {
  int temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

/*****************************************************************************/

void voidswap(void **p1, void **p2) {
    void *temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/*****************************************************************************/

/*prints an array of integers for testing*/
void print_int_array(int A[], int n) {
  int i;
  for (i=0; i < n; i++) {
      printf("%3d", A[i]);
  }
}

/*****************************************************************************/

/*prints anonymous string data*/
void print_data(void *data_v) {
    char **data = data_v;
    printf("%6s", *data);
}

/*****************************************************************************/

/*gets the max of two integers*/
int intmax(int n1, int n2) {
    if (n1 > n2) return n1;
    return n2;
}

/*****************************************************************************/

int stringcmp(void *v1, void *v2) {
    char *s1 = v1, *s2 = v2;
    return strcmp(s1, s2);
}

/*****************************************************************************/
void *stringcpy(void *str) {
    char *new;
    int size = strlen(str) + 1;

    new = (char*)malloc(sizeof(*new)*size);
    assert(new);

    new = strcpy(new, str);
    assert(new);

    return new;
}

/*****************************************************************************/
int next_pow2(int num) {
    int ret = 2;
    while (ret < num) {
        ret *= 2;
    }
    return ret;
}

/*****************************************************************************/

int intcmp(void *v1, void *v2) {
    int *n1=v1, *n2=v2;
    return *n1 - *n2;
}

/*****************************************************************************/
