#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 1 << 30;

int N;
int dist[500010];
bool seen[500010];
ii res[500010];
vvii edges;

ii Dijkstra(const int s) {
   priority_queue<ii, vector<ii>, greater<ii>> Q;
   int tot = 0;
   int furthest = -1;
   Q.push(ii(0, s));
   for (int i = 0; i <= N; i++)
      dist[i] = INF;
   dist[s] = 0;
   ii curr;
   while (!Q.empty()) {
      curr = Q.top();
      Q.pop();
      if (dist[curr.second] < curr.first)
         continue;
      if (curr.first > furthest)
         furthest = curr.first, tot = 1;
      else
         tot++;
      for (auto& it : edges[curr.second]) {
         if (curr.first + it.second < dist[it.first]) {
            dist[it.first] = curr.first + it.second;
            Q.push(ii(dist[it.first], it.first));
         }//if
      }//for
   }//while
   return ii(furthest, tot);
}//Dijkstra

int main() {
   int M, Q, q, A, B, L;
   scanf("%d %d %d", &N, &M, &Q);
   edges.assign(N + 5, vii());
   while (M--) {
      scanf("%d %d %d", &A, &B, &L);
      edges[A].push_back(ii(B, L));
      edges[B].push_back(ii(A, L));
   }//while
   while (Q--) {
      scanf("%d", &q);
      if (!seen[q]) {
         res[q] = Dijkstra(q);
         seen[q] = 1;
      }//if
      printf("%d %d\n", res[q].first, res[q].second);
   }//while
   return 0;
}//main
