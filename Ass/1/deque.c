#include <stdio.h>
#include <stdlib.h>

typedef long long int Llint;

typedef struct N {
	Llint data;
	struct N * next;
	struct N * prev;
} Node;

typedef struct Deque {
	Llint count;
	Node * front;
	Node* rear;
} Deq;

Deq * pushf(Deq* ends, Llint dat) {

	if(ends->count == 0) {
		Node* fr;
		Node* re;

		fr = (Node *)malloc(sizeof(Node));
		fr->next = NULL;
		fr->prev = NULL;
		fr->data = dat;
		re = fr;

		Deq * cat = (Deq*)malloc(sizeof(Deq));
		cat->front = fr;
		cat->rear = re;
		cat->count = 1;

		free(ends);

		return cat;
	}


	Node * f = NULL;
	f = (Node*)malloc(sizeof(Node));

	Node * t = ends->front; // getting the old front

	f->data = dat; // new front data
	f->next = t; // new front points to old front
	f->prev = NULL; // new front points back to null

	t->prev = f; // old front points back to new front

	t = ends->rear; // getting the rear

	Deq * fron = (Deq*)malloc(sizeof(Deq));
	fron->front = f; // new Struct
	fron->rear = t; 
	fron->count = (ends->count + 1);
	// now, old struct is of no use.
	free(ends);

	return fron;
}

Deq * pushr(Deq* ends, Llint dat) {

	if(ends->count == 0) {
		Node* fr;
		Node* re;

		fr = (Node *)malloc(sizeof(Node));
		fr->next = NULL;
		fr->prev = NULL;
		fr->data = dat;
		re = fr;

		Deq * cat = (Deq*)malloc(sizeof(Deq));
		cat->front = fr;
		cat->rear = re;
		cat->count = 1;

		free(ends);

		return cat;
	}


	Node * r = NULL;
	r = (Node*)malloc(sizeof(Node));

	Node * t = ends->rear; // Getting old rear

	r->data = dat; // making new rear
	r->next = NULL; // new rear points forward to nothing
	r->prev = t; // new rear points back to old rear

	t->next = r; // old rear points to new rear

	t = ends->front; // Getting the front

	Deq * fron = (Deq*)malloc(sizeof(Deq));
	fron->front = t;
	fron->rear = r; 
	fron->count = (ends->count + 1);

	// NR
	free(ends);

	return fron;
}

Deq * popf(Deq* ends) {
	if(ends->count == 0) {
		return ends;
	}

	if(ends->count == 1) {
		ends->rear = NULL;
		ends->front = NULL;
		ends->count -= 1;
		return ends;
	}

	Node * t = ends->front; // to free memory
	ends->front = ends->front->next; // the front changes
	ends->front->prev = NULL; // new front points back to nothing
	free(t);
	ends->count -= 1;
	
	return ends;
}

Deq * popr(Deq* ends) {
	if(ends->count == 0) {
		return ends;
	}

	if(ends->count == 1) {
		ends->rear = NULL;
		ends->front = NULL;
		ends->count -= 1;
		return ends;
	}

	Node * t = ends->rear; // to free memory
	ends->rear = ends->rear->prev; // rear is prev to current rear
	ends->rear->next = NULL;
	ends->count -= 1;
	free(t);

	return ends;
}

void print(Deq* cat) {
	if(cat->count == 0) {
		printf("Queue Underflow\n");
	}
	Node * p = cat->front;
	printf("------------------------\nPrinting\n\n");
	for (; p != NULL ; p = p->next)
	{
		printf("%lld\n", p->data);
	}
	printf("\nDone\n------------------------\n");
}

int main()
{
	Node* fr = NULL;
	Node* re = NULL;
	/* code */
	Llint temp;
	fr = NULL;
	re = fr;

	Deq * cat = (Deq*)malloc(sizeof(Deq));
	cat->front = fr;
	cat->rear = re;
	cat->count = 0;

	for (int i = 0; i < 100; ++i) {
		printf("1 for pushf, 2 for pushr, 3 for popf, 4 for popr\n");
		scanf("%lld", &temp);

		if(temp == 1) {
			printf("Enter Value:\n");
			scanf("%lld", &temp);

			cat = pushf(cat, temp);
		}
		else if(temp == 2) {
			printf("Enter Value:\n");
			scanf("%lld", &temp);
			cat = pushr(cat, temp);
		}
		else if(temp == 3) {
			if(cat->count != 0)
				printf("Front of Queue is : %lld\n", cat->front->data);
			cat = popf(cat);
		}
		else {
			if(cat->count != 0)
				printf("Back of Queue is : %lld\n", cat->rear->data);
			cat = popr(cat);
		}
		print(cat);
	}
	return 0;
}