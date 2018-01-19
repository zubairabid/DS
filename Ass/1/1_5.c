#include <stdio.h>
#include <stdlib.h>


typedef long long int Llint;

// implement dequeues: pushf, pushr, popf, popr

typedef long long int Llint;
Llint mod = 1e9 + 7;

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

long long int pwo(long long int base, long long int pow, long long int mod) {
	long long int res = 1;
	
	while(pow > 0) {
	
		if(pow % 2 == 1) {
			pow--;
			res = (res * base)%mod;
		}
	
		pow /= 2;
		base = (base * base)%mod;
	
	}

	return res;
}

long long int minv(long long int a) {

	if(a != mod) {
		return ((pwo(a, mod-2, mod))%mod);	
	}
	else {
		return -1;
	}
	
	return 0;
}

Llint moddiv(Llint a, Llint b) {
	a = a % mod;
	b = b % mod;
	return ((a*minv(b))%mod);
}


Llint modmultiply(Llint a, Llint b) {
	Llint ret = (((a%mod)*(b%mod))%mod);
	return ret;
}




int main() {
	Llint max_ = 1, min_ = 1, div_ = 1;
	Llint i, j, k, n, T;

	Llint arr[100007];


	scanf("%lld %lld", &n, &k);
	for (i = 0; i < n; ++i) {
		scanf("%lld", &arr[i]);
	}

	Node* fr = NULL;
	Node* re = NULL;
	/* code */
	Llint temp;
	fr = NULL;
	re = fr;

	Deq * greater = (Deq*)malloc(sizeof(Deq));
	greater->front = fr;
	greater->rear = re;
	greater->count = 0;

	Deq * smaller = (Deq*)malloc(sizeof(Deq));
	smaller->front = fr;
	smaller->rear = re;
	smaller->count = 0;

	// Computing it.

	//Populating initial k window. All iterations combine to form the window 
	for (i = 0; i < k; ++i) {
		// Any elements in *smaller greater than element[i] is never gonna be smallest in the window
		if((smaller->count != 0) && arr[(smaller->rear->data)] >= arr[i]) {// TODO TODO TODO
			smaller = popr(smaller);
		}
		// Any elements in *greater smaller than element[i] is never gonna be greatest in the window
		if((greater->count != 0) && arr[(greater->rear->data)] <= arr[i]) {// TODO TODO TODO
			greater = popr(greater);
		}

		// Add i to rear of greater and smaller
		greater = pushr(greater, i);
		smaller = pushr(smaller, i);
	}

	printf("in initial window: max = arr[%lld] = %lld, min = arr[%lld] = %lld\n", greater->front->data, arr[greater->front->data], smaller->front->data, arr[smaller->front->data]);


	// Multiply the max and min of the first window
	max_ = modmultiply(max_, arr[greater->front->data]);
	min_ = modmultiply(min_, arr[smaller->front->data]);


	// Populate remaining windows 1 by 1. Each iteration covers a new window
	for (i = k; i < n; ++i) {
		// Remove any older data: all indices i-k are irrelevant at each iteration of i
		while(smaller->count != 0 && smaller->front->data <= i-k) {
			smaller = popf(smaller);
		}
		while(greater->count != 0 && greater->front->data <= i-k) {
			greater = popf(greater);
		}

		// Any elements in *smaller greater than element[i] is never gonna be smallest in the window
		while(smaller->count != 0 && arr[smaller->rear->data] >= arr[i]) {
			printf("arr[%lld]=%lld >= arr[%lld]=%lld, popping rear\n", smaller->rear->data, arr[smaller->rear->data], i, arr[i]);
			smaller = popr(smaller);
		}

		// Any elements in *greater smaller than element[i] is never gonna be greatest in the window
		while(greater->count != 0 && arr[greater->rear->data] <= arr[i]) {
			printf("arr[%lld]=%lld <= arr[%lld]=%lld, popping rear\n", greater->rear->data, arr[greater->rear->data], i, arr[i]);
			greater = popr(greater);
		}
 

 		// Add i to rear of greater and smaller
		greater = pushr(greater, i);
		smaller = pushr(smaller, i);

		printf("in window: max = arr[%lld] = %lld, min = arr[%lld] = %lld\n", greater->front->data, arr[greater->front->data], smaller->front->data, arr[smaller->front->data]);

		// Multiply the max and min of the current window
		max_ = modmultiply(max_, arr[greater->front->data]);
		min_ = modmultiply(min_, arr[smaller->front->data]);

		printf("max: %lld, min = %lld\n\n", max_, min_);


	}
	div_ = moddiv(max_, min_);
	printf("%lld\n", div_);

	return 0;
}