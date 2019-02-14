#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

int A[200010];

int main() {
   int T, N, K;
   int l, r;
   int ans;
   scanf("%d", &T);
   while (T--) {
      scanf("%d %d", &N, &K);
      K++;
      priority_queue<ii, vector<ii>, greater<ii>> Q1;
      priority_queue<ii, vector<ii>> Q2;
      for (int i = 0; i < N; i++)
         scanf("%d", &A[i]);
      l = 0;
      r = min(N - 1, K);
      for (int i = 0; i <= r; i++)
         Q1.push(ii(A[i], i)), Q2.push(ii(A[i], i));
      ans = 0;
      while (l < N) {
         while (Q1.top().second <= l - K - 1)
            Q1.pop();
         while (Q2.top().second <= l - K - 1)
            Q2.pop();
         ans = max(ans, max(Q2.top().first - A[l], A[l] - Q1.top().first));
         l++;
         if (r < N - 1) {
            r++;
            Q1.push(ii(A[r], r)), Q2.push(ii(A[r], r));
         }//if
      }//while
      printf("%d\n", ans);
   }//while
   return 0;
}//main
