#include <stdio.h>
#include "structures/priority_queue.h"

/* Test for binary heap's heapify() method */

void heapify (unsigned int *array, unsigned int len);
main() {
    unsigned int foo[20] = {19, 15, 23, 5, 9, 4, 17, 25, 69, 7, 23, 5, 11, 3, 1, 8, 33, 0, 12, 14};
    struct priority_queue bar;
    int i;

    bar.elems = foo;
    bar.n_elems = 19;

    heapify(foo, 19);

    for (i = 0; i < 19; i++) {
        printf("%d\n", pq_extract(&bar));
    }
}
