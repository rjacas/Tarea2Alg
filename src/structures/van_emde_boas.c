#include "priority_queue.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
  
  
struct priority_queue *pq_new(int size,int universe) {
    struct priority_queue *p;
	int i,new_universe;
	
    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->n_elems = 0;
    p->min = INT_MIN;
    p->max = INT_MAX;
    p->universo = (int)pow(2,universe);
    p->top = NULL;
    //entonces hay (por ahora ignorando redondeo) 2^(B/2) hijos con 2^(B/2) elementos cada uno
	
	p->nhijos = (int)pow(2,universe/2);
    
    p->atrees = (struct array_trees *)malloc(sizeof(struct array_trees)*p->nhijos);
    
    for (i = 0; i < p->nhijos; i++)
		p->atrees[i].pq_child = pq_new_bottom(universe/2,p);
    
    return p;
}

struct priority_queue *pq_new_bottom(int universe,struct priority_queue *top) {
    struct priority_queue *p;
    int i;

    p = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    p->n_elems = 0;
    p->min = INT_MIN;
    p->max = INT_MAX;
    p->universo = (int)pow(2,universe);
    p->top = top;
    p->nhijos = 0;
    
    if(universe > 1){
    
		p->nhijos = (int)pow(2,universe/2);

		p->atrees = (struct array_trees *)malloc(sizeof(struct array_trees)*p->nhijos);
		
		for (i = 0; i < p->nhijos; i++)
			p->atrees[i].pq_child = pq_new_bottom(universe/2,p);
	}
	else{
		p->atrees = NULL;
	}
    
    return p;
}

int pq_empty(struct priority_queue *p) {
    int i;
    
    for(i = 0; p->nhijos; i++)
		if(p->atrees[i].non_empty == 1)
			return 0;
			
	return 1;
}

void pq_insert(struct priority_queue *pq, int new_elem) {
    int i, tmp, h, l;

#ifdef DEBUG
    if (pq->n_elems == pq->elems[0]) {
        printf("Max elems in priority queue exceeded.\n");
        exit(1);
    }
#endif

    pq->n_elems++;
    printf("ya sume\n");
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
	}
	else {
		if (new_elem < pq->min) {
			printf("soy menor que el minimo\n");
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
		
	if(pq->atrees != NULL){	
		
		printf("debo bajar\n");
		
		h = higher(new_elem,pq->universo);
		l = lower(new_elem,pq->universo);
		
		printf("h: %d\n",h);
		printf("l: %d\n",l);
		pq_insert (pq->atrees[h].pq_child,l);
	
	
		if (pq->atrees[h].pq_child->n_elems == 1)
			pq_insert_in_top(pq->top,h);
	}
}

int pq_extract(struct priority_queue *pq) {
	
	int min;
	
	min = pq->min;
	
	pq_up_min(pq);
	
	return min;
	
}


void pq_up_min(struct priority_queue *pq) {
    int i=-1;

#ifdef DEBUG
    if (pq->n_elems == 0) {
        printf("No elements to extract from priority queue.\n");
        exit(1);
    }
#endif
	
	if(pq->n_elems == 1)
		return;

	pq->n_elems--;
	
	if (pq->n_elems == 1) 
		pq->min = pq->max;
	
	
	else {			
		if(pq->atrees != NULL){
			for(i = 0; i < pq->nhijos; i++)
				if(pq->atrees[i].non_empty == 1)
					break;
				
			pq->min = pq->atrees[i].pq_child->min;
		}
	}
	
	if(i != -1){
		
		pq_up_min(pq->atrees[i].pq_child);
	
		if (pq->atrees[i].pq_child->n_elems == 0)
			if(pq->top != NULL)
				pq_delete_in_top(pq->top,i);
				
	}

}

void pq_delete_in_top(struct priority_queue *pq,int h){
	
	pq->atrees[h].non_empty = 0;

}

void pq_insert_in_top(struct priority_queue *pq,int h){
	
	pq->atrees[h].non_empty = 1;
	
}

void pq_free(struct priority_queue *p) {
    
    int i;
    
    if(p->nhijos != 2){
		for(i = 0; p->nhijos; i++)
			pq_free(p->atrees[i].pq_child);
		
		free(p->atrees);
	}
    
    free(p);
}

int higher(int x, int universo) {
	int mascarado = 7 >> (int)ceil((log(universo)/log(2))/2);
	
	printf("calculando higher\n");
	printf("numero de shifts %x\n",(int)ceil((log(universo)/log(2))/2));
	printf("0 negado %x\n",~0);
	printf("mascara %x\n",mascarado);
	return (x & (~0 >> (int)ceil((log(universo)/log(2))/2)));
}

int lower(int x, int universo) {
	printf("calculando lower\n");
	return (x & (~0 << (int)floor((log(universo)/log(2))/2)));
}