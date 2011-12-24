#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "priority_queue.h"


struct priority_queue *pq_new(int size) {
    struct priority_queue *p;

    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->elems = (int *) malloc (sizeof(int)*(size + 1));
    p->n_elems = 0;
    p->elems[0] = size;
    return p;
}

int pq_empty(struct priority_queue *p) {
    return ((p->n_elems == 0)? TRUE : FALSE);
}

void pq_insert(struct priority_queue *pq, int new_elem) {
    int i, tmp;

#ifdef DEBUG
    if (pq->n_elems == pq->elems[0]) {
        printf("Max elems in priority queue exceeded.\n");
        exit(1);
    }
#endif

    pq->n_elems++;
    pq->elems[pq->n_elems] = new_elem;

    for (i = pq->n_elems; i > 1 && pq->elems[i] <= pq->elems[i/2]; i /= 2) {
        tmp = pq->elems[i];
        pq->elems[i] = pq->elems[i/2];
        pq->elems[i/2] = tmp;
   }
}

int pq_extract(struct priority_queue *pq) {
    int tmp, i, j, elem;

#ifdef DEBUG
    if (pq->n_elems == 0) {
        printf("No elements to extract from priority queue.\n");
        exit(1);
    }
#endif
    elem = pq->elems[1];

    pq->elems[1] = pq->elems[pq->n_elems];
    pq->n_elems--;
    i = 1;

    while (2 * i <= pq->n_elems) {
        j = 2 * i;
        if ((j + 1) <= pq->n_elems && pq->elems[j+1] < pq->elems[j]) j++;

        if (pq->elems[i] < pq->elems[j]) break;

        tmp = pq->elems[i];
        pq->elems[i] = pq->elems[j];
        pq->elems[j] = tmp;

        i = j;
    }

    return elem;
}

void pq_free(struct priority_queue *p) {
    free(p->elems);
    free(p);
}
