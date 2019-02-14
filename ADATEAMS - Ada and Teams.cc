#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
typedef long long LL;

int powmod(LL a, int b) {
   LL res = 1;
   while (b) {
      if (b & 1)
         res *= a, res %= MOD;
      a = (a * a) % MOD;
      b >>= 1;
   }//while
   return (int)res;
}//powmod

LL fac[1000010];

int main() {
   fac[0] = 1;
   for (int i = 1; i <= 1000000; i++)
      fac[i] = i * fac[i - 1], fac[i] %= MOD;
   int T, N, A, B, D;
   LL r1, r2;
   while (scanf("%d %d %d %d", &N, &A, &B, &D) == 4) {
      r1 = (((fac[N] * powmod(fac[N - A], MOD - 2)) % MOD) * (powmod(fac[A], MOD - 2))) % MOD;
      r2 = powmod(((((fac[B] * powmod(fac[B - D], MOD - 2)) % MOD) * (powmod(fac[D], MOD - 2))) % MOD), A);
      printf("%d\n", (r1 * r2) % MOD);
   }//while
   return 0;
}//main
