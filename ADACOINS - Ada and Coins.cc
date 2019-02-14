#include <bits/stdc++.h>
using namespace std;

bitset<100001> sum;
int DP[100010];

void fr(int &to) {
   char t; to ^= to;
   while (!isdigit((t = getchar())));
   while (t > 47) { to = (to << 3) + (to << 1) + t - 48; t = getchar(); }
}//fr

int main() {
   int N, Q, v, L, R;
   fr(N); fr(Q);
   for (int i = 0; i < N; i++) {
      fr(v);
      sum |= (sum << v);
      sum.set(v);
   }//for
   for (int i = 1; i <= 100000; i++)
      DP[i] = DP[i - 1] + sum.test(i);
   while (Q--) {
      fr(L); fr(R);
      printf("%d\n", DP[R] - DP[L - 1]);
   }//while
   return 0;
}//main
