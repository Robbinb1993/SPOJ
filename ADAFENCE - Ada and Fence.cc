#include <bits/stdc++.h>
using namespace std;

int flag[10000010];
int D[100010];

int main() {
   int T, N, K, req, sum1, sum2, ans;
   scanf("%d", &T);
   for (int t = 1; t <= T; t++) {
      scanf("%d %d", &N, &K);
      sum1 = 0;
      for (int i = 0; i < N; i++)
         scanf("%d", &D[i]), sum1 += D[i];
      req = sum1 / K;
      ans = sum2 = 0;
      for (int i = 0; i < N; i++) {
         if (sum2 < req)
            flag[sum2] = t;
         else
            flag[sum2] = flag[sum2 - req];
         if (sum2 + req >= sum1 && flag[(sum2 + req) % sum1] == t)
            ans += (flag[sum2] == t);
         sum2 += D[i];
      }//for
      printf("%d\n", ans);
   }//while
   return 0;
}//main
