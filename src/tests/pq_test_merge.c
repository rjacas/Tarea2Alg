#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"
#define N_ELEMS 10
int main(int argc, char **argv) {
    int aux, i;
    struct priority_queue *p1,*p2, *p3;
    int elems[N_ELEMS] = { 79, 2, 2, 2, 2, 1, 2, 2, 79, 79};
		int elems2[N_ELEMS] = { 4, 3, 72, 4, 77, 2, 83, 7, 15, 22};
		int elems3[N_ELEMS] = { 4, 3, 72, 4, 77, 2, 83, 7, 15, 22};
    p1 = pq_new(N_ELEMS,7);
		p2 = pq_new(N_ELEMS,7);
		p3 = pq_new(N_ELEMS,7);

    for (i = 0; i < N_ELEMS; i++) {
        printf("Inserting1 %d...\n", elems[i]);
        pq_insert(p1, elems[i]);   
    }
    for (i = 0; i < N_ELEMS; i++) {
        printf("Inserting2 %d...\n", elems2[i]);
        pq_insert(p2, elems2[i]); 
    }
    for (i = 0; i < N_ELEMS; i++) {
        printf("Inserting3 %d...\n", elems3[i]);
        pq_insert(p3, elems3[i]);  
    }
		printf("Merging...\n");
		pq_merge(p1, p2);
		pq_merge(p1, p3);

    for (i = 0; i < 3*N_ELEMS; i++) {
        aux = pq_extract(p1);
        printf("Extracted: %d\n", aux);
    }

    pq_free(p1);
}

