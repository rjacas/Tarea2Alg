#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"

#define timespec_diff_ns(timeA_p, timeB_p) ((timeA_p.tv_sec - timeB_p.tv_sec)*1000000000 + (timeA_p.tv_nsec - timeB_p.tv_nsec))

#define timespec_diff_ms(timeA_p, timeB_p) ((timeA_p.tv_sec - timeB_p.tv_sec)*1000 + (timeA_p.tv_nsec - timeB_p.tv_nsec)/1000000)

struct priority_queue *pq_merge(struct priority_queue *p1, struct priority_queue *p2);

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
    unsigned int exp_universe, big, exp_n, n, n_1, i, j, m, repeats, alpha;
    struct priority_queue *pq, *pq1, *pq2;
    unsigned int *elems;
    unsigned int idx;
    struct timespec before, after;

    if (argc < 6) {
        printf("Usage : run_once exp_universe exp_n percentage filename repetitions big\n");
        printf("Example : run_once 11 5 16 test_file 2 1 will run a test with:\n \t2^16 integers in the range [0,...2^11 - 1]\n\tOne of the structures will hold approximately 16 percent of the elements; the remaining amount will be in the other.\n\tThe test will be repeated (without any change in the input integers) 2 times.\n\tThe test is big so times will be measured in ms.\n");
        exit(1);
    }

    big = atoi(argv[6]);
    exp_universe = atoi(argv[1]); 
    exp_n = atoi(argv[2]); 
    alpha = atoi(argv[3]); 
    repeats = atoi(argv[5]);
    n = 1 << exp_n;

    n_1 = (alpha * n) / 100; 

    elems = gen_instance(argv[4], n, exp_universe);


    for (m = 0; m < repeats; m++) {

    pq1 = pq_new(n_1, exp_universe);
    pq2 = pq_new(n - n_1, exp_universe);


    for (i = 0; i < n_1; i++) {
        pq_insert(pq1, elems[i]);
    }
    for (; i < n; i++) {
        pq_insert(pq2, elems[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &before);
    pq = pq_merge(pq1, pq2);
    clock_gettime(CLOCK_MONOTONIC, &after);

    if (big) {
        printf("merge: %lldms\n", timespec_diff_ms(after, before));
    } else {
        printf("merge: %ldns\n", timespec_diff_ns(after, before));
    }

    pq_free(pq);
    }
    free(elems);
}



