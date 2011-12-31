#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"
#define DEFAULT_N 20

int main(int argc, char **argv) {
    int n_elems, aux, i;
    struct priority_queue *pq;
    if (argc < 2) {
        n_elems = DEFAULT_N;
    } else {
        n_elems = atoi(argv[1]);
    }

    pq = pq_new(n_elems, 100);

    for (i = 0; i < n_elems; i++) {
        aux = random() % 100;
        printf("Inserting %d...\n", aux);
        pq_insert(pq, aux);   
    }

    for (i = 0; i < n_elems; i++) {
        aux = pq_extract(pq);
        printf("Extracted: %d\n", aux);
    }

    pq_free(pq);
}

