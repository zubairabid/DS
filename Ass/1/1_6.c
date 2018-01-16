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
	if(type == p2) {
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
			if(exist[i] == 1) {
				temp = pop(1);
				if(temp == i) {
					c++; // sorted
				}
				else {
					push(2, temp);
					moves++;
				}
			}
			else if(exist[i] == 2) {
				temp = pop(2);
				if(temp == i) {
					c++; // sorted
				}
				else {
					push(1, temp);
					moves++;
				}
			}
		}
	}

	printf("%lld\n", moves);

	return 0;
}