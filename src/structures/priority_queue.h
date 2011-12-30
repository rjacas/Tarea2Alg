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
    unsigned int *elems;
    unsigned int n_elems;
};

#endif

/* ===================== Splay Tree ===================== */
#ifdef _SPLAY_TREE

struct node{
    struct node *parent;
    struct node *left, *right;
    unsigned int value;
};

struct priority_queue {
    struct node *root;
};
/* Tree operations */
struct node *node_insert(struct node *root, struct node *new_node);
void node_free(struct node *n);
struct node *node_min(struct node *n);

/* Splay Tree rotations */
void splay(struct node *n);
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
    unsigned int value;
    unsigned int order;
};

struct priority_queue {
    struct node **trees;
    unsigned int total_trees;
    unsigned int n_elems;
};

void merge_tree(struct priority_queue *p, struct node *new_node);
void merge_all_trees_rec(struct priority_queue *p, struct node *n);
#endif

/* ===================== Fibonacci Heap ===================== */
#ifdef _FIBONACCI_HEAP

#define MAXKEY 16777215
int node_count;
int node_created_flag;
int init_n;
int n;
int hn;
int na;
struct node *nodes_array[MAXKEY];
struct l_node *first;

struct node{
	int tag;
	int key;
	int degree;
	struct node *left;
	struct node *child;
	struct node *parent;
	struct node *right;
  struct node *back;
};

struct priority_queue{
	struct node *root_list;
	int n_nodes;
};

struct l_node{
	struct node *addr;
	struct l_node *link;
};

struct priority_queue *new_pq();
int get_min(struct priority_queue *pq);
struct node *link_node(struct node *t1,struct node *t2);
void consolidate(struct priority_queue *pq);
//worse implementation, but it works :D (worse on memory usage)//
struct l_node *node_list(unsigned int n);
void make_node_list(int n);
struct node *get_node();
void put_node(struct node *tnode);
#endif

/* ===================== Van Emde Boas Tree ===================== */
#ifdef _VAN_EMDE_BOAS

#ifndef _UNIVERSE
#define _UNIVERSE 100
#endif

struct array_trees {
	
	struct priority_queue *pq_child;
	int non_empty;
	
};
 
 
struct priority_queue {
	
	int min;
	int max;
	int n_elems;	
	int universo;
	int nhijos;
	struct array_trees *atrees;
	struct priority_queue *top;
	
};

struct priority_queue *pq_new_bottom(int size,struct priority_queue *top);
void pq_up_min(struct priority_queue *pq);
void pq_delete_in_top(struct priority_queue *pq,int h);
void pq_insert_in_top(struct priority_queue *pq,int h);
int higher(int x, int universo);
int lower(int x, int universo);


#endif

/* 
   Creates a new priority_queue structure, which should be
   deallocated through pq_free().

Params:
    size(IN) - the number of elements the priority_queue will
    be able to hold.

	universe(IN) - the size of the universe (range of numbers
	that we can have in a priority_queue).
Returns:
    the newly created priority_queue structure.
*/
struct priority_queue *pq_new(unsigned int size, unsigned int universe);

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
void pq_insert(struct priority_queue *p, unsigned int new_elem);

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

unsigned int pq_extract(struct priority_queue *p);

/*
   Deallocates a priority queue created through pq_new(). Unspecified
   behavior will happen if a null priority queue, an already freed
   priority_queue or a priority queue that wasn't allocated through
   pq_new() is freed with this function.

Params:
    p(IN/OUT) - the priority queue to be freed.
*/
void pq_free(struct priority_queue *p);

#if defined(_BINARY_HEAP) || defined(_BINOMIAL_HEAP) || defined(_FIBONACCI_HEAP)
/*
	 Merges two priority queues into one, absorbing the second queue
     into the first. Both priority_queue structs must have been
     allocated through pq_new(). The resulting priority queue (p1)
     will have a maximum number of elements equal to the sum of the
     maximums of each merged queue. Duplicate elements will not be
     deleted.
 
Params:
      p1(IN/OUT) - the first priority queue to be merged. After the
                    merge, it will hold all the merged elements.
      p2(IN/OUT) - the second priority queue to be merged. After the
                    merge it will be freed. In other words, this pointer
                    will be unusable after the merging.

*/
void pq_merge(struct priority_queue *p1, struct priority_queue *p2);
#endif


#endif
