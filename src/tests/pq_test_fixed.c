#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"
#define N_ELEMS 7
int main(int argc, char **argv) {
    int aux, i;
    struct priority_queue *pq;
    int elems[N_ELEMS] = { 4, 3, 72, 4, 77, 2, 83};

    pq = pq_new(N_ELEMS, 100);

    for (i = 0; i < N_ELEMS; i++) {
        printf("Inserting %d...\n", elems[i]);
        pq_insert(pq, elems[i]);   
    }

    for (i = 0; i < N_ELEMS; i++) {
        aux = pq_extract(pq);
        printf("Extracted: %d\n", aux);
    }

    //pq_free(pq);
}

