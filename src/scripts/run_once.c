#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"

unsigned int *gen_instance(char *filename, unsigned int n, unsigned int universe);

int main(int argc, char **argv) {
    unsigned int exp_universe, exp_n, n, k, i, j, n_elems;
    struct priority_queue *pq;
    unsigned int *elems;
    unsigned int idx;

    if (argc < 5) {
        printf("Usage : run_once exp_universe k exp_n filename\n");
        exit(1);
    }

    exp_universe = atoi(argv[1]); 
    k = atoi(argv[2]); 
    exp_n = atoi(argv[3]); 

    n = 1 << exp_n;
    n_elems = k * n;

    pq = pq_new(n_elems, exp_universe);

    //Maximum size is 84 MB. Still addressable, bitches. 
    elems = gen_instance(argv[4], 3 * k * n, exp_universe);

    idx = 0;
    for (i = 0; i < n; i++) {
        printf("Run number %d\n", i);
        for (j = 0; j < k; j++) { printf("Inserted %d\n", elems[idx]); pq_insert(pq, elems[idx++]); }
        for (j = 0; j < k; j++) { printf("Extracted %d\n", pq_extract(pq)); }
        for (j = 0; j < k; j++) { printf("Inserted  %d\n", elems[idx]); pq_insert(pq, elems[idx++]); }
    }

    //medir aqui
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) pq_extract(pq);
        for (j = 0; j < k; j++) pq_insert(pq, elems[idx++]);
        for (j = 0; j < k; j++) pq_extract(pq);
    }

    //medir aca

    free(elems);
    pq_free(pq);
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

