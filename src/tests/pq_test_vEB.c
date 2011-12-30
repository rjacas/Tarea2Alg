#include <stdlib.h>
#include <stdio.h>
#include "../structures/priority_queue.h"


void printvEB(struct priority_queue *p,int tabs){
	int i;	
		
	for(i = 0; i < tabs; i++)
		printf("\t");
	printf("min: %d, max %d\n",p->min,p->max);
	
	for(i = 0; i < tabs; i++)
		printf("\t");
	printf("n_elems: %d, nhijos: %d\n",p->n_elems,p->nhijos);
	
	for(i = 0; i < tabs; i++)
		printf("\t");
	printf("universo %d\n",p->universo);
	
	for(i = 0; i < p->nhijos; i++)
		printvEB(p->atrees[i].pq_child,tabs+1);
	
}

int main(){
	
	struct priority_queue *pq;
	int i;
	pq = pq_new(0,4);
	
	int nums[7];
	
	nums[0] = 14; 
	nums[1] = 7; 
	nums[2] = 5; 
	nums[3] = 15; 
	nums[4] = 3; 
	nums[5] = 4; 
	nums[6] = 2; 
	
	//~ printvEB(pq,0);
	//~ 
	for(i = 0; i < 7; i++){
		printf("Inserting %d...\n",nums[i]);
		pq_insert(pq,nums[i]);
		printvEB(pq,0);
	}
	
	//~ printvEB(pq,0);
}





