#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <math.h>
#include "priority_queue.h"


struct priority_queue *pq_new(int size) {
    struct priority_queue *pq;
    pq = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    pq->total_trees = 0;
    pq->n_elems = 0;

    return pq;
}

int pq_empty(struct priority_queue *p) {
    return ((p->n_elems == 0)? TRUE : FALSE);
}

void pq_insert(struct priority_queue *pq, int new_elem) {
    struct node *new_node;
    new_node = (struct node *)malloc(sizeof(struct node));
		new_node->parent = NULL;
    new_node->left = NULL;
		new_node->right = NULL;
		new_node->child = NULL;
    new_node->value = new_elem;
    new_node->degree = 0;
		new_node->mark = FALSE;
    insert_tree(pq, new_node);
	  pq->total_trees++;
    pq->n_elems++;		
}

int pq_extract(struct priority_queue *pq) {
	int min;	
	struct node *aux;
	aux = cut_node_root(pq,pq->min);
	min = aux->value;
	free(aux);
	return min;
}

void pq_free(struct priority_queue *p) {//mal
    /*int i;
    i = 0;
    while (p->n_elems << i != 0) {
        if ((p->n_elems << i) & 1) {
            free(p->trees[i]);
        }
        i++;
    }

    free(p->trees);
    free(p);*/
}

priority_queue *pq_merge(struct priority_queue *p1, struct priority_queue *p2){
	struct node *i, *aux;	
	i = p2->min->right;
	do{
			if(i != NULL){
				aux = cut_node_root(p2, i);
				i = i->right;	
				insert_tree(p1,aux);		
			}	
	}
	while(i != NULL && i != p2->min);
	aux = cut_node_root(p2, p2->min);
	insert_tree(p1,aux);
}

void insert_tree(struct priority_queue *p, struct node *new_node){
	struct node *aux;	
	if(p->min == NULL)
		p->min = new_node;
	else{
		new_node->left = p->min;
		if(p->min->right != NULL){
			new_node->right = p->min->right;
			p->min->right->left = new_node;							
		}
		else{
			p->min->left = new_node;
			new_node->right = p->min;
						
		}
		p->min->right = new_node;	
	}
	if(new_node->value < p->min->value)
		p->min = new_node;

		new_node->mark = FALSE;
}

void insert_sub_tree(struct node *par, struct node *chi){
	chi->right->left = chi->left;
	chi->left->right = chi->right;
	if(par->child == NULL){
		par->child = chi;
		chi->parent = par;
		chi->left = NULL;
		chi->right = NULL;
		par->degree += chi->degree + 1;
	}
	else{
		chi->left = par->child->right;
		if(par->child->right != NULL){
			chi->right = par->child->right;
			par->child->right->left = chi;							
		}
		else{
			par->child->left = chi;
			chi->right = par->child;
						
		}
		par->child->right = chi;
		par->degree += chi->degree + 1;	
	}
}

struct node *cut_node_root(struct priority_queue *pq, struct node *tnode){
	struct node *i,*aux;	
	if(tnode == NULL) return;

	if(tnode->degree > 0){
		tnode->child->parent = NULL;
		
		aux = i = tnode->child->right;
		do{
			if(i->right != NULL){
				aux = i;
				i->left->right = i->right;
				i->right->left = i->left;
				insert_tree(pq, i);					
			}
			i = i->right;
		}
		while(aux != NULL && aux != tnode->child);
		insert_tree(pq, tnode->child);	
	}	
	if(tnode->right != NULL){
		tnode->right->left = tnode->left;
		tnode->left->right = tnode->right;
	}
	pq->total_trees--;
	pq->n_elems--;
	consolidate(pq);
	return tnode;
}

void consolidate(struct priority_queue *pq){
	int max_degree;
	struct node *i,*aux;
	struct node **degrees;
	max_degree = (int)ceil(log(pq->n_elems)/log((1+sqrt(5))/2));
	degrees = (struct node **) malloc(sizeof(struct node *) * max_degree);
	i = pq->min;
	degrees[i->degree] = i;
	do{
			if(i != NULL){
				if(degrees[i->degree] != NULL)
					degrees[i->degree] = i;
				else{
					if(degrees[i->degree]->value <= i->value){
						aux = cut_node_root(pq, degrees[i->degree]);
						degrees[i->degree] = i;	
						insert_sub_tree(i, aux);
					}
					else{
						aux = cut_node_root(pq,i);	
						insert_sub_tree(degrees[i->degree], aux);						
					}		
				}			
			}
			i = i->right;		
	}
	while(i != NULL && i != pq->min);
	free(degrees);
}

