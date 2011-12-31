#ifndef _SPLAY_TREE
#define _SPLAY_TREE
#endif
#include <stdlib.h>
#include "priority_queue.h"
#ifdef DEBUG
#include <stdio.h>
#endif

struct priority_queue *pq_new(unsigned int size, unsigned int universe) {
    struct priority_queue *pq;

    pq = (struct priority_queue *)malloc(sizeof(struct priority_queue *));

    pq->root = NULL;

    return pq;
}

int pq_empty(struct priority_queue *p) {
    
    return (p->root == NULL)? TRUE : FALSE;
}

void pq_insert(struct priority_queue *p, unsigned int new_elem) {
    struct node *new_node;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->left = new_node->right = new_node->parent = NULL;

    new_node->value = new_elem;
    p->root = node_insert(p->root, new_node);

    splay(new_node);
    p->root = new_node;
}

unsigned int pq_extract(struct priority_queue *p) {
    struct node *min_node;
    unsigned int ret;
    #ifdef DEBUG
    if (pq_empty(p)) {
        printf("No elements to extract from priority queue.\n");
        exit(1);
    }
    #endif
 
    min_node = node_min(p->root);
    splay(min_node);
    p->root = min_node;
    p->root = p->root->right;

    if (p->root != NULL) p->root->parent = NULL;

    ret = min_node->value;
    free(min_node);
    return ret; 
}

void pq_free(struct priority_queue *p) {
    node_free(p->root);
    free(p);
}

void splay(struct node *n) {
    struct node *dad, *grandpa;
    dad = n->parent;
    if (dad == NULL) return;

    grandpa = dad->parent;

    if (grandpa == NULL) {
        /* We're root's childrens */
        if (n == dad->left) {
            zig(n, dad);
        } else { 
            zag(n, dad);
        }
        return;
    }

    if (n == dad->left && dad == grandpa->left) {
        zigzig(n, dad, grandpa);
    } else if (n == dad->right && dad == grandpa->left) {
        zag(n, dad);
        zig(n, grandpa);
    } else if (n == dad->left && dad == grandpa->right) {
        zig(n, dad);
        zag(n, grandpa);
    } else if (n == dad->right && dad == grandpa->right) {
        zagzag(n, dad, grandpa);
    }

    splay(n);

}

void zig(struct node *son, struct node *dad) {
    
    dad->left = son->right;
    if (dad->left != NULL) dad->left->parent = dad;

    son->right = dad;

    if (dad->parent != NULL) {
        if (dad->parent->left == dad) dad->parent->left = son;
        else dad->parent->right = son;
    }

    son->parent = dad->parent;
    dad->parent = son;
}

void zag(struct node *son, struct node *dad) {
    
    dad->right = son->left;
    if (dad->right != NULL) dad->right->parent = dad;

    son->left = dad;

    if (dad->parent != NULL) {
        if (dad->parent->left == dad) dad->parent->left = son;
        else dad->parent->right = son;
    }

    son->parent = dad->parent;
    dad->parent = son;
}

void zigzig(struct node *son, struct node *dad, struct node *grandpa) {
    
    son->parent = grandpa->parent;

    grandpa->left = dad->right;
    if (grandpa->left != NULL) grandpa->left->parent = grandpa;

    dad->left = son->right;
    if (dad->left != NULL) dad->left->parent = dad;

    son->right = dad;
    dad->parent = son;

    if (grandpa->parent != NULL) {
        if (grandpa->parent->left == grandpa) grandpa->parent->left = son;
        else grandpa->parent->right = son;
    }

    dad->right = grandpa;
    grandpa->parent = dad;
}

void zagzag(struct node *son, struct node *dad, struct node *grandpa) {
   
    son->parent = grandpa->parent;

    grandpa->right = dad->left;
    if (grandpa->right != NULL) grandpa->right->parent = grandpa;

    dad->right = son->left;
    if (dad->right != NULL) dad->right->parent = dad;

    son->left = dad;
    dad->parent = son;

    if (grandpa->parent != NULL) {
        if (grandpa->parent->left == grandpa) grandpa->parent->left = son;
        else grandpa->parent->right = son;
    }

    dad->left = grandpa;
    grandpa->parent = dad;
}

struct node *node_insert(struct node *root, struct node *new_node) {
    
    if (root == NULL) return new_node;
    
    new_node->parent = root;

    if (new_node->value > root->value) {
        root->right = node_insert(root->right, new_node);
    } else if (new_node->value <= root->value) {
        root->left = node_insert(root->left, new_node);
    }

    return root;
}

struct node *node_min(struct node *root) {
    return (root->left == NULL)? root : node_min(root->left);
}

void node_free(struct node *n) {
    if (n == NULL) return;

    node_free(n->left);
    node_free(n->right);

    free(n);

}

