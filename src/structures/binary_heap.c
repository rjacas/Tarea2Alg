#ifndef _BINARY_HEAP
#define _BINARY_HEAP
#endif

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "priority_queue.h"

void heapify (unsigned int *array, unsigned int len);

struct priority_queue *pq_new(unsigned int size, unsigned int universe) {
    struct priority_queue *p;

    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->elems = (unsigned int *) malloc (sizeof(unsigned int)*(size + 1));
    p->n_elems = 0;
    p->elems[0] = size;
    return p;
}

int pq_empty(struct priority_queue *p) {
    return ((p->n_elems == 0)? TRUE : FALSE);
}

void pq_insert(struct priority_queue *pq, unsigned int new_elem) {
    unsigned int i, tmp;

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

unsigned int pq_extract(struct priority_queue *pq) {
    unsigned int tmp, i, j, elem;

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

struct priority_queue *pq_merge(struct priority_queue *p1, struct priority_queue *p2) {
    unsigned int i;
    struct priority_queue *pq1, *pq2;

    if (p1->n_elems < p2->n_elems) {
        pq2 = p1;
        pq1 = p2;
    } else {
        pq1 = p1;
        pq2 = p2;
    }

    pq1->elems = realloc(pq1->elems, sizeof(unsigned int) * (pq1->elems[0] + pq2->elems[0] + 1));

    pq1->elems[0] = pq1->elems[0] + pq2->elems[0];

    for (i = 1; i < pq2->n_elems + 1; i++) {
        pq1->elems[i + pq1->n_elems] = pq2->elems[i];
    }

    pq1->n_elems += pq2->n_elems;

    heapify(pq1->elems + 1, pq1->n_elems);
    pq_free(pq2);

    return pq1;
}

void heapify (unsigned int *array, unsigned int len) {
    unsigned int i, j, k, aux;
    i = len / 2;
    while (i >= 1) {
        j = i;
        while (j * 2 <= len) {
            k = 2 * j;

            if ((k + 1) <= len && array[k + 1] < array[k]) k++;

            if (array[j] < array[k]) break;

            aux = array[j];
            array[j] = array[k];
            array[k] = aux;

            j = k;
        }

        i--;
    }

}


void pq_free(struct priority_queue *p) {
    free(p->elems);
    free(p);
}
