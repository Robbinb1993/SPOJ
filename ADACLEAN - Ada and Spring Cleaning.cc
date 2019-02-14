#include <bits/stdc++.h>
using namespace std;
const int PRIME_BASE = 719;
long long int PRIME_MOD = 1110111110111ULL;

inline long long int mulmod(long long int a, long long int b) {
	long long int res = 0;
	while (a > 0) {
		if (a & 1)
			res = (res + b) % PRIME_MOD;
		a >>= 1;
		b = (b << 1) % PRIME_MOD;
	}
	return res;
}

int main() {
   int T, N, k, len;
   set<unsigned long long int> strings;
   long long int hash;
   long long int power;
   char haystack[102000];
   scanf("%d", &T);
   while (T--) {
      hash = 0;
      power = 1;
      strings.clear();
      scanf("%d %d", &N, &k);
		getchar();
      gets(haystack);
      len = strlen(haystack);
      if (k <= len) {
         for (int i = 0; i < k; i++)
            power = mulmod(power, PRIME_BASE);
         for (int i = 0; i < k; i++) {
            hash = mulmod(hash, PRIME_BASE) + haystack[i];
            hash %= PRIME_MOD;
         }//for
         strings.insert(hash);
         for (int i = k; i < N; i++) {
            hash = mulmod(hash, PRIME_BASE) + haystack[i];
            hash %= PRIME_MOD;
            hash -= mulmod(power, haystack[i - k]);
            if (hash < 0)
               hash += PRIME_MOD;
            strings.insert(hash);
         }//for
         printf("%d\n", (int)strings.size());
      }//if
      else
         printf("0\n");
   }//while
   return 0;
}//main
