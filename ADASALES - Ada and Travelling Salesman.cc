#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> LLLL;
typedef vector<LLLL> vLLLL;

vector<vector<int>> edges;
vLLLL m1, m2;
bool seen[100010];
int A[100010];

void setPath(const int u, const int v) {
   LL w = max(0, A[v] - A[u]);
   LL p = (m1[v].second != u) ? m1[v].first : m2[v].first;
   if (w + p > m1[u].first) {
      m2[u] = m1[u];
      m1[u].first = w + p;
      m1[u].second = v;
   }//if
   else if (w + p > m2[u].first) {
      m2[u].first = w + p;
      m2[u].second = v;
   }//else if
}//setPath

void DFS0(const int u) {
   seen[u] = 1;
   for (auto& e : edges[u]) {
      if (!seen[e]) {
         DFS0(e);
         setPath(u, e);
      }//if
   }//for
}//DFS0

void DFS1(const int u, const int prv) {
   seen[u] = 1;
   setPath(u, prv);
   for (auto& e : edges[u])
      if (!seen[e])
         DFS1(e, u);
}//DFS1

int main() {
   int N, Q, n1, n2;
   scanf("%d %d", &N, &Q);
   edges.assign(N + 10, vector<int>());
   m1.assign(N + 10, LLLL(0, 0));
   m2.assign(N + 10, LLLL(0, 0));
   for (int i = 0; i < N; i++)
      scanf("%d", &A[i]);
   for (int i = 0; i < N - 1; i++) {
      scanf("%d %d", &n1, &n2);
      edges[n1].push_back(n2);
      edges[n2].push_back(n1);
   }//for
   DFS0(0);
   memset(seen, 0, sizeof(seen));
   DFS1(0, N);
   while (Q--) {
      scanf("%d", &n1);
      printf("%lld\n", m1[n1].first);
   }//while
   return 0;
}//main
