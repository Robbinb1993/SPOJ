#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

int main() {
   int T, N, M, q;
   int t, v;
   scanf("%d", &T);
   while (T--) {
      scanf("%d %d %d", &N, &M, &q);
      set<int> S[2];
      set<int>::iterator it1, it2;
      priority_queue<iii, vector<iii>> Q[2];
      S[0].insert(0); S[0].insert(N); S[1].insert(0); S[1].insert(M);
      Q[0].push(iii(N, ii(0, N)));
      Q[1].push(iii(M, ii(0, M)));
      while (q--) {
         scanf("%d %d", &t, &v);
         if (v != 0 && !((t == 0 && v == N) || (t == 1 && v == M))) {
            it1 = S[t].lower_bound(v);
            it1--;
            it2 = S[t].upper_bound(v);
            S[t].insert(v);
            Q[t].push(iii(*it2 - v, ii(v, *it2)));
            Q[t].push(iii(v - *it1, ii(*it1, v)));
         }//if
         while (*(S[t].upper_bound(Q[t].top().second.first)) < Q[t].top().second.second)
            Q[t].pop();
         printf("%lld\n", LL(Q[0].top().first) * Q[1].top().first);
      }//while
   }//while
   return 0;
}//main
