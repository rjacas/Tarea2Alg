#ifndef _FIBONACCI_HEAP
#define _FIBONACCI_HEAP
#endif

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <math.h>
#include "priority_queue.h"


struct priority_queue *pq_new(unsigned int size, unsigned int universe) {
	struct priority_queue *pq;
	make_node_list(size);
  pq = new_pq();
	pq->init_n = size;
  return pq;
}

int pq_empty(struct priority_queue *p) {
  return ((p->n_nodes == 0)? TRUE : FALSE);
}

void pq_insert(struct priority_queue *p, unsigned int new_elem) {
	if(new_elem < MAXKEY){
		struct node *new_node;
		if(nodes_array[new_elem] == NULL){
			new_node = get_node();	
			nodes_array[new_elem] = new_node;
		}
		else{
			struct l_node *temp;
			new_node = (struct node *) malloc(sizeof(struct node));		
			put_node(new_node);
		}
		new_node->parent = NULL;
		new_node->child = NULL;
		new_node->degree = 0;
		new_node->key = new_elem;
		new_node->tag = 0;
		new_node->left = new_node;
		new_node->right = new_node;		
		if(p->n_nodes == 0){
			p->root_list = new_node;
			p->n_nodes = 1;
		}
		else{
			new_node->left = p->root_list;
			new_node->right = p->root_list->right;
			p->root_list->right = new_node;
			new_node->right->left = new_node;
			if((p->root_list->key) > (new_node->key))
				p->root_list = new_node;
			p->n_nodes+=1;
		}
	}
	#ifdef DEBUG
	else
		printf("Key %d can not be inserted. Maximum allowable key is %d\n",new_elem,MAXKEY);
	#endif
}

unsigned int pq_extract(struct priority_queue *p){
	if(p->root_list != NULL){
		int temp;
		struct node *tempptr,*t1,*t2;
		temp = p->root_list->key;
		if((p->root_list->child == NULL) && (p->n_nodes == 1)){
			put_node(p->root_list);
			p->n_nodes = 0;
			p->root_list = NULL;
		}
		else if ((p->root_list->child == NULL) && (p->n_nodes > 1)){	
			p->root_list->left->right = p->root_list->right;
			p->root_list->right->left = p->root_list->left;
			tempptr = p->root_list;
			p->root_list = p->root_list->left;
			put_node(tempptr);
			p->n_nodes -= 1;
			if(p->root_list->key != 3)
				consolidate(p);
		}
		else if(p->root_list->child != NULL){
			t1 = p->root_list->child;
			while(t1 != t1->right ){
				t2=t1->right;
				t1->right = t2->right;
				t2->right->left = t1;
			
				t2->right= p->root_list->right;
				t2->left = p->root_list;
				t2->parent=NULL;
				t2->tag = 0;

				p->root_list->right->left = t2;
				p->root_list->right = t2;
				p->n_nodes += 1;
			}
				t1->right= p->root_list->right;
				t1->left = p->root_list;
				t1->parent = 0;
				t1->tag = 0;
				p->root_list->right->left = t1;
				p->root_list->right = t1;
				p->n_nodes += 1;
				p->root_list->degree = 0;
				t2 = p->root_list;
				p->root_list->left->right = p->root_list->right;
				p->root_list->right->left = p->root_list->left;
				p->root_list = p->root_list->right;
				put_node(t2);
				p->n_nodes -=1;
				consolidate(p);
		}
		return temp;
	}
	#ifdef DEBUG
	else{
		printf("priority_queue is Empty.\n");
		return -1;
	}
	#endif
}

void pq_free(struct priority_queue *p) {
		struct node* aux;

		while(node_count > 0){
			aux = get_node();
			free(aux);
		}
		node_created_flag = FALSE;
		free(p);
}

struct priority_queue *pq_merge(struct priority_queue *p1, struct priority_queue *p2){
	struct priority_queue *p3;
	struct node *t1;
	if(p1->root_list == NULL){	
		p3 = p2;
		p2 = NULL;
	}
	else if(p2->root_list == NULL){	
		p3 = p1;
		p1 = NULL;
	}
	else if (p1->root_list == NULL && p2->root_list == NULL)
		p3 = NULL;
	else{
		p3 = p1;	
		p1->root_list->right->left = p2->root_list->left;
		p2->root_list->left->right = p1->root_list->right;
		p1->root_list->right = p2->root_list;
		p2->root_list->left=p1->root_list;

		if((p2->root_list->key) < (p1->root_list->key))
			p1->root_list = p2->root_list;
		p3->n_nodes = p1->n_nodes + p2->n_nodes;

		free(p2);
		p2 = NULL;
		p1 = NULL;
	}
	return p3;
}


struct priority_queue *new_pq(){
	struct priority_queue *pq;
	pq = (struct priority_queue*) malloc(sizeof(struct priority_queue));
	pq->root_list = NULL;
	pq->n_nodes = 0;
	#ifdef DEBUG
	printf("PQ %d created.\n",hn);
	#endif
	hn += 1;
	return pq;
}

int get_min(struct priority_queue *pq){	
	return pq->root_list->key;
}

struct node *link_node(struct node *t1,struct node *t2){
	if((t1->child == NULL) && (t1->degree == 0)){	
		t1->child = t2;
		t1->degree += 1;
		t2->parent = t1;
		t2->left = t2;
		t2->right = t2;
		return t1;
	}
	else{	
		t2->parent = t1;
		t1->degree += 1;
		t2->right = t1->child->right;
		t2->left = t1->child;
		t1->child->right->left = t2;
		t1->child->right = t2;
		return t1;
	}
}

void consolidate(struct priority_queue *pq){
	int i,x,d;
	
	struct node *t1,*t2,*temp;
	x = pq->n_nodes * (ceil(log(pq->init_n)/log((1+sqrt(5))/2)));
	struct node *array[x];

	for(i = 0; i < x; i++)
		array[i] = NULL;
	
	
	t1 = pq->root_list;
	temp = t1->right;

	for(i = 1; i <= pq->n_nodes; i++){	
		d = t1->degree;
		while(array[d] != 0){
			t2 = array[d];
			if(t1->key < t2->key)	
				t1 = link_node(t1,t2);
			else
				t1 = link_node(t2,t1);
			array[d] = 0;
			d = d+1;
		}
		array[d] = t1;
		t1 = temp;
		temp = temp->right;
	}
	pq->root_list = NULL;
	pq->n_nodes = 0;
	for(i = 0; i < x; i++){
		if(array[i] != 0){
			if(pq->root_list == NULL){
				pq->root_list = array[i];
				pq->root_list->left = pq->root_list->right = pq->root_list;
				pq->n_nodes = 1;
			}
			else{	
				array[i]->left = pq->root_list;
				array[i]->right = pq->root_list->right;
				pq->root_list->right->left = array[i];
				pq->root_list->right = array[i];
				pq->n_nodes += 1;
				if(array[i]->key < pq->root_list->key)
					pq->root_list = array[i] ;
			}
		}
	}
}

struct l_node *node_list(unsigned int n){
	int i;
	struct l_node *h, *temp;
	struct node *tnode;
	if(node_created_flag)
		h = first;
	else
		h = NULL;
	node_created_flag = TRUE;
	for(i = 1; i <= n;i++)	{
		temp = (struct l_node *) malloc(sizeof(struct l_node));
		tnode = (struct node *) malloc(sizeof(struct node));
	
		temp->link = h;
		temp->addr = tnode;
		tnode->back = NULL;
		h = temp;
	}
	node_count += n;
	#ifdef DEBUG
	printf("%d Nodes Created.\n",n);
	#endif
	return h;
}

void make_node_list(int n){	
	first = node_list(n);
}

struct node *get_node(){
	struct l_node *temp;
	struct node *tnode;
	tnode = first->addr;
	temp = first;
	first = first->link;
	free(temp);
	node_count = node_count--;
	return tnode;
}

void put_node(struct node *tnode){
	struct l_node *temp;
	temp = (struct l_node *) malloc(sizeof(struct l_node));
	temp->addr = tnode;
	temp->link = first;
	first = temp;
	node_count = node_count++;
}


