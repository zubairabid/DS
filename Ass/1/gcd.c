#include <stdio.h>

typedef long long int Llint;

/*
	a > b
*/
Llint gcd(Llint a, Llint b) {
	if(b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

int main() {
	Llint a, b, mod = 1e9 + 7;
	scanf("%lld %lld", &a, &b);

	printf("%lld\n", gcd(a, b));
}