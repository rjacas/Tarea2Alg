#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"

#define timespec_diff(timeA_p, timeB_p) ((timeA_p.tv_sec - timeB_p.tv_sec)*1000 + (timeA_p.tv_nsec - timeB_p.tv_nsec)/1000000)

int int_cmp(const void *a, const void *b) {

    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    if (*ia == *ib) {
        return 0;
    } else if (*ia < *ib) {
        return -1;
    } else {
        return 1;
    }
}

void semisort(unsigned int *elems, unsigned int size) {
    int i1, i2, i, n_swaps;
    unsigned int aux;
    
    n_swaps = size/4;

    srandom(time(NULL));

    for (i = 0; i < n_swaps; i++) {
        i1 = random() % size;
        i2 = random() % size;

        aux = elems[i1];
        elems[i1] = elems[i2];
        elems[i2] = aux;
    }

}

unsigned int *gen_instance(char *filename, unsigned int n, unsigned int exp_universe) {
    unsigned int *elems;
    int idx, ret;
    FILE *file;

    elems = (unsigned int *)malloc(n * sizeof(unsigned int));
    
    file = fopen(filename, "rb");

    idx = 0;

    while ((ret = fread(elems + idx, sizeof(unsigned int), n - idx, file)) > 0 && (n - idx) > 0) idx += ret;
   
    fclose(file);

    return elems;
}

int main(int argc, char **argv) {
    unsigned int exp_universe, exp_n, n, k, i, j, m, repeats, sorted;
    struct priority_queue *pq;
    unsigned int *elems;
    unsigned int idx;
    struct timespec before, after;

    if (argc < 6) {
        printf("Usage : run_once exp_universe k exp_n filename repetitions sort_type\n");
        printf("Order means: 0 for unsorted files; 1 for completely sorted; 2 for semi-sorted.\n");
        printf("Example : run_once 11 5 16 test_file 2 0 will run a test with:\n \tIntegers in the range [0,...2^11 - 1]\n\tUsing 2^16 sequences of 5 insertions, 5 deletions and 5 insertions, followed by 2^16 inverse sequences.\n\tThe test will be repeated (without any change in the input integers) 2 times.\n\tThe inserted elements will not be sorted before insertion.\n");
        exit(1);
    }

    exp_universe = atoi(argv[1]); 
    k = atoi(argv[2]); 
    exp_n = atoi(argv[3]); 
    repeats = atoi(argv[5]);
    n = 1 << exp_n;

    pq = pq_new(k * n, exp_universe);

    elems = gen_instance(argv[4], 3 * k * n, exp_universe);

    sorted = atoi(argv[6]);

    if (sorted) {
        qsort(elems, 3 * k * n, sizeof(unsigned int), int_cmp); 
    }

    if (sorted == 2) {
        semisort(elems, 3 * k * n);
    }

    for (m = 0; m < repeats; m++) {
    idx = 0;

    clock_gettime(CLOCK_MONOTONIC, &before);
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) pq_insert(pq, elems[idx++]);
        for (j = 0; j < k; j++) pq_extract(pq);
        for (j = 0; j < k; j++) pq_insert(pq, elems[idx++]);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    printf("idi: %lldns\t", timespec_diff(after, before));
   
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) pq_extract(pq);
        for (j = 0; j < k; j++) pq_insert(pq, elems[idx++]);
        for (j = 0; j < k; j++) pq_extract(pq);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    
    printf("did: %lldns\n", timespec_diff(after, before));

    }
    free(elems);
    pq_free(pq);
}



