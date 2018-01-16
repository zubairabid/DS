#include <stdio.h>
#include <stdlib.h>

long long int exist[1007];
long long int s1[1007]; // stack 1
long long int s2[1007]; // stack 2
long long int p1 = -1, p2 = -1;


void push(long long int type, long long int val) {
	if(type == 1) {
		p1++;
		s1[p1] = val;
	}
	if(type == 2) {
		p2++;
		s2[p2] = val;
	}
}

long long int pop(long long int type) {
	//not testing for underflow
	if(type == 1) {
		p1--;
		return s1[p1+1];
	}
	if(type == 2){
		p2--;
		return s2[p2+1];
	}
}


int main() {
	long long int i, n, j, k, temp, c, moves = 0;

	//input 
	scanf("%lld", &n);
	for (i = 0; i < n; ++i) {
		scanf("%lld", &temp);
		exist[temp] = 1; // push to s1
		push(1, temp);
	}

	for (i = 0, c = 1; c <= n ; ++i)
	{
		if(exist[i] == 0) {
			continue;
		}
		else {
			if(exist[i] == 1 && p1 >= 0) {
				// printf("Looking in stack 1. Head at %lld\n", p1);

				temp = pop(1);

				// printf("Value: %lld, looking for %lld\n", temp, i);

				if(temp == i) {
					// printf("Pop 1\n");
					c++; // sorted
				}
				else {
					// printf("Move 1 2\n");
					push(2, temp);
					i--;
					moves++;
					exist[temp] = 2;
				}
			}
			else if(exist[i] == 2 && p2 >= 0) {
				// printf("Looking in stack 2. Head at %lld\n", p2);
				temp = pop(2);

				// printf("Value: %lld, looking for %lld\n", temp, i);

				if(temp == i) {
					// printf("Pop 2\n");
					c++; // sorted
				}
				else {
					// printf("Move 2 1\n");
					push(1, temp);
					i--;
					moves++;
					exist[temp] = 1;
				}
			}
			else {
				// printf("Failed both tests somehow. exist[%lld] = %lld, p1 = %lld, p2 = %lld\n",i, exist[i], p1, p2);
			}
		}
	}

	printf("%lld\n", moves);

	return 0;
}