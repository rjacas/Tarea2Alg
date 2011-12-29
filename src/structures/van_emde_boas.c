#include "priority.h"
 
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
 
struct priority_queue *pq_new(int size) {
    struct priority_queue *p;
	int i;
	
    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->n_elems = 0;
    p->min = INT_MIN;
    p->max = INT_MAX;
    p->universo = size;
    p->top = NULL;
    
    pq->nhijos = (int)((log(size)/log(2))/2);
     
    pq->atrees = (struct array_trees *)malloc(sizeof(struct array_trees)*pq->nhijos);
    
    for (i = 0; i < pq->nhijos; i++)
		pq->atrees[i] = pq_new_bottom(pq->nhijos,p);
    
    return p;
}

struct priority_queue *pq_new_bottom(int size,struct priority_queue *top) {
    struct priority_queue *p;
    int i;

    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->n_elems = 0;
    p->min = INT_MIN;
    p->max = INT_MAX;
    p->universo = size;
    p->top = top;
    p->nhijos = 0;
    
    if(size > 2){
    
		pq->nhijos = (int)((log(size)/log(2))/2);
		 
		pq->atrees = (struct array_trees *)malloc(sizeof(struct array_trees)*pq->nhijos);
		
		for (i = 0; i < pq->nhijos; i++)
			pq->atrees[i] = pq_new_bottom(pq->nhijos,p);
	}
	else{
		pq->atrees = NULL;
	}
    
    return p;
}

int pq_empty(struct priority_queue *p) {
    int i;
    
    for(i = 0; p->nhijos; i++)
		if(p->atrees[i]->non_empty == 1)
			return = 0;
			
	return 1;
}

void pq_insert(struct priority_queue *pq, unsigned int new_elem) {
    int i, tmp;

#ifdef DEBUG
    if (pq->n_elems == pq->elems[0]) {
        printf("Max elems in priority queue exceeded.\n");
        exit(1);
    }
#endif

    pq->n_elems++;
    
    if (pq->n_elems == 1) {
			pq->max = new_elem;
			pq->min = new_elem;
			return;
		}
		
	else if (pq->n_elems == 2) {
		
		if (new_elem < pq->min) {
			pq->min = new_elem;
			return;
		}
		else {
			pq->max = new_elem;
			return;
		}
	
	else {
		if (new_elem < pq->min) {
			tmp = pq->min;
			pq->min = new_elem;
			new_elem = tmp;
		}
		
		else if (new_elem > pq->max) {
			tmp = pq->max;
			pq->max = new_elem;
			new_elem = tmp;
		}
	}
		
	h = higher(new_elem);
	l = lower(new_elem);

	pq_insert (pq->atrees[h],l);
	
	if (pq->atrees[h]->n_elems == 1)
		pq_insert_in_top(pq->top,h);
}

int pq_extract(struct priority_queue *pq) {
	
	int min,i;
	
	if (pq->universo == 2){
		min = pq->min;
		pq_delete(pq,pq->min);
		return min;
	}
		
	for(i = 0; i < algo; i++)
		if (pq->atrees[i]->non_empty == 1)
			return pq_extract_min(pq->atrees[i]->pq_child)

	
}

void pq_delete(struct priority_queue *pq, unsigned int del_elem) {
    int tmp, i, j, elem;

#ifdef DEBUG
    if (pq->n_elems == 0) {
        printf("No elements to extract from priority queue.\n");
        exit(1);
    }
#endif

	pq->n_elems--;
	
	if (pq->n_elems == 1) { 
		
		if (del_elem == pq->max)
			pq->max = pq->min;
		
		else
			pq->min = pq->max;
	
	}
	
	else {
		
		if (del_elem == pq->max) {
			pq->atrees[higher(del_elem)]->max = pq->top->max;
			pq->max = amax(raiz de U) + max (arbol # amax);
			del_elem = pq->max;
		}

		if (del_elem == pq->min) {
			pq->atrees[higher(del_elem)]->min = pq->top->min;
			pq->min = amin(raiz de U) + min (arbol # amin);
			del_elem = pq->min;
		}
	}
	
	h = higher(new_elem);
	l = lower(new_elem);

	pq_delete(pq->atrees[h],l);
	
	if (pq->atrees[h]->n_elems == 0)
		if(pq->top != NULL)
			pq_delete_in_top(pq->top,h);

}

void pq_delete_in_top(struct priority_queue *pq,int h){
	
	pq->atrees[h]->non_empty = 0;
	
}

void pq_insert_in_top(struct priority_queue *pq,int h){
	
	pq->atrees[h]->non_empty = 1;
	
}

void pq_free(struct priority_queue *p) {
    
    int i;
    
    if(p->nhijos != 2){
		for(i = 0; p->nhijos; i++)
			pq_free(p->atrees[i]->pq_child);
		
		free(p->atrees);
	}
    
    free(p);
}

int higher(int x, int universo) {
	return (x & ((~0) >>ceil(log(universo)/log(2)*2)));
}

int lower(int x, int universo) {
	return (x & ((~0) >>floor(log(universo)/log(2)*2)));
}
