#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int A[15];

int main() {
   int N, M;
   LL prod, ans;
   while (scanf("%d %d", &N, &M) == 2) {
      ans = 0;
      for (int i = 0; i < M; i++)
         scanf("%d", &A[i]);
      for (int i = 1; i < (1 << M); i++) {
         prod = 1;
         for (int j = 0; j < M; j++) {
            if ((1 << j) & i) {
               prod = prod * (A[j] / __gcd((int)prod, A[j]));
               if (prod > N)
                  break;
            }//if
            if (j == M - 1) {
               if (__builtin_popcount(i) & 1)
                  ans += N / prod;
               else
                  ans -= N / prod;
            }//if
         }//for
      }//for
      printf("%lld\n", N - ans);
   }//while
   return 0;
}//main
