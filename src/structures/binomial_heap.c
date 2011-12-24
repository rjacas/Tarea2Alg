#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include "priority_queue.h"

struct priority_queue *pq_new(int size) {
    struct priority_queue *pq;

    pq = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    
    pq->total_trees = (int) ceil(log(size + 1)/log(2));
    pq->trees = (struct node **) malloc(sizeof(struct node *) * pq->total_trees);
    pq->n_elems = 0;

    return pq;
}

void pq_insert(struct priority_queue *p, int new_elem) {
    struct node *new_node;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->bro = NULL;
    new_node->first_child = NULL;
    new_node->value = new_elem;
    new_node->order = 0;

    merge_tree(p, new_node);

}

int pq_extract(struct priority_queue *p) {
    int i, min_i, val;
    struct node *aux;
    val = INT_MAX;
    for (i = 0; (p->n_elems >> i) != 0 ; i++) {
        if ((p->n_elems >> i) & 1) {
            if (val > p->trees[i]->value) {
                val = p->trees[i]->value;
                min_i = i;
            }
        }

    }

    aux = p->trees[min_i]->first_child;
    free(p->trees[min_i]);
    p->trees[min_i] = NULL;

    p->n_elems &= ~(1 << min_i);
    if (aux != NULL) merge_all_trees_rec(p, aux);

    return val;
}

void merge_all_trees_rec(struct priority_queue *p, struct node *n) {
    if (n->bro != NULL) {
        merge_all_trees_rec(p, n->bro);
    } 

    n->bro = NULL;
    merge_tree(p, n);
}

int pq_empty(struct priority_queue *p) {
    return (p->n_elems == 0)? TRUE : FALSE;
}

void pq_free(struct priority_queue *p) {
    int i;
    i = 0;
    while (p->n_elems << i != 0) {
        if ((p->n_elems << i) & 1) {
            free(p->trees[i]);
        }
        i++;
    }

    free(p->trees);
    free(p);
}

void merge_tree(struct priority_queue *p, struct node *new_node) {
    struct node *father, *son, *aux;
    int order;

    order = new_node->order;
    if (p->n_elems & (1 << order)) {
        father = (p->trees[order]->value < new_node->value)? p->trees[order] : new_node;
        son = (p->trees[order]->value >= new_node->value)? p->trees[order] : new_node;

        aux = father->first_child;
        father->first_child = son;
        son->bro = aux;
        father->order++;
        
        p->trees[order] = NULL;
        p->n_elems &= ~(1 << order);
        merge_tree(p, father);

    } else {
        p->trees[order] = new_node;
        p->n_elems |= (1 << order);
    }

} 
