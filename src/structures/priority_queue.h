#ifndef _PRIORITY_QUEQUE_
#define _PRIORITY_QUEQUE_

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ===================== Binary Heap ===================== */
#ifdef _BINARY_HEAP

struct priority_queue {
    int *elems;
    int n_elems;
};

#endif

/* ===================== Splay Tree ===================== */
#ifdef _SPLAY_TREE

struct node{
    struct node *parent;
    struct node *left, *right;
    int value;
};

struct priority_queue {
    struct node *root;
};

void splay(struct node *n);
struct node *node_insert(struct node *root, struct node *new_node);
void node_free(struct node *n);
struct node *node_min(struct node *n);
void zag(struct node *son, struct node *dad); 
void zig(struct node *son, struct node *dad); 
void zigzig(struct node *son, struct node *dad, struct node *grandpa); 
void zagzag(struct node *son, struct node *dad, struct node *grandpa); 
#endif

/* ===================== Binomial Heap ===================== */

#ifdef _BINOMIAL_HEAP

struct node {
    struct node *bro;
    struct node *first_child;
    int value;
    int order;
};

struct priority_queue {
    struct node **trees;
    int total_trees;
    int n_elems;
};

void merge_tree(struct priority_queue *p, struct node *new_node);
void merge_all_trees_rec(struct priority_queue *p, struct node *n);
#endif

/* ===================== Fibonacci Heap ===================== */
#ifdef _FIBONACCI_HEAP
#endif

/* ===================== Van Emde Boas Tree ===================== */
#ifdef _VAN_EMDE_BOAS
#endif

/* 
   Creates a new priority_queue structure, which should be
   deallocated through pq_free().

Params:
    size(IN) - the number of elements the priority_queue will
    be able to hold.

Returns:
    the newly created priority_queue structure.
*/
struct priority_queue *pq_new(int size);

/*
   Tests a priority queue for emptiness

Params:
    p(IN) - the priority queue to test for emptiness.

Returns:
    TRUE if the priority_queue was empty, FALSE if it
    wasn't.
*/

int pq_empty(struct priority_queue *p);

/*
    Inserts an element in the priority queue, along with an identifier
    for the origin of it. Unspecified behavior will happen if an
    insertion is made on a full priority queue.

Params:
    p(IN) - the priority queue where the element will be inserted.
    new_elem(IN) - the element to insert.

*/
void pq_insert(struct priority_queue *p, int new_elem);

/*
   Extracts the smallest element and its origin identifier from a
   priority queue. Undefined behavior will happen if the smallest
   element from an empty priority queue is extracted.

Params: 
    p(IN) - the priority queue from which to extract the smallest
    element and its origin.
    elem(OUT) - pointer to where the smallest element in the
    priority queue should be left.
    origin(OUT) - pointer to where the origin identifier of the
    smallest element in the priority queue should be left.
*/

int pq_extract(struct priority_queue *p);

/*
   Deallocates a priority queue created through pq_new(). Unspecified
   behavior will happen if a null priority queue, an already freed
   priority_queue or a priority queue that wasn't allocated through
   pq_new() is freed with this function.

Params:
    p(IN/OUT) - the priority queue to be freed.
*/
void pq_free(struct priority_queue *p);
#endif
