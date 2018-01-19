#include <stdio.h>

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

int main() {
	long long int base, pow, mod = 1e9 + 7;

	scanf("%lld %lld", &base, &pow);
	printf("%lld\n", pwo(base, pow, mod));

	return 0;
}