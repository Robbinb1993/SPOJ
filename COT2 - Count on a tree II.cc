#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

map<int, int> getID;
map<int, int>::iterator it;

const int LOGN = 20;
int id, bs, N;
int counter[50050];
int A[50050], P[100050];
int res[100050];
int st[50050], ed[50050];
int DP[20][50050], level[50050];
bool flag[50050];
bool seen[50050];
vvi edges;

struct Q {
   int l, r, p, id;
   bool operator < (const Q& other) const {
      return (l / bs < other.l / bs || (l / bs == other.l / bs && r < other.r));
   }//operator <
} q[100050];

void DFS0(const int u) {
   seen[u] = 1;
   P[id] = u;
   st[u] = id++;
   for (auto& e : edges[u]) {
      if (!seen[e]) {
         DP[0][e] = u;
         level[e] = level[u] + 1;
         DFS0(e);
      }//if
   }//for
   P[id] = u;
   ed[u] = id++;
}//DFS0

void prep(const int r) {
   level[r] = 0;
   for (int i = 0; i < LOGN; i++)
      DP[i][r] = r;
   id = 0;
   DFS0(r);
   for (int i = 1; i < LOGN; i++)
      for (int j = 1; j <= N; j++)
         DP[i][j] = DP[i - 1][DP[i - 1][j]];
}//prep

int LCA(int a, int b) {
   if (level[a] > level[b])
      swap(a, b);
   int diff = level[b] - level[a];
   for (int i = 0; i < LOGN; i++)
      if (diff & (1 << i))
         b = DP[i][b]; //move 2^i parents upwards
   if (a == b)
      return a;
   for (int i = LOGN - 1; i >= 0; i--)
      if (DP[i][a] != DP[i][b])
         a = DP[i][a], b = DP[i][b];
   return DP[0][a];
}//LCA

int main() {
   int Q, n1, n2, L, R, a, v = 1, tot;
   scanf("%d %d", &N, &Q);
   edges.assign(N + 5, vi());
   bs = sqrt(N);
   for (int i = 1; i <= N; i++) {
      scanf("%d", &a);
      A[i] = ((it = getID.find(a)) != getID.end()) ? it->second : (getID[a] = v++);
   }//for
   for (int i = 0; i < N - 1; i++) {
      scanf("%d %d", &n1, &n2);
      edges[n1].push_back(n2);
      edges[n2].push_back(n1);
   }//for
   prep(1);
   for (int i = 0; i < Q; i++) {
      scanf("%d %d", &n1, &n2);
      if (st[n1] > st[n2])
         swap(n1, n2);
      q[i].p = LCA(n1, n2);
      if (q[i].p == n1)
         q[i].l = st[n1], q[i].r = st[n2];
      else
         q[i].l = ed[n1], q[i].r = st[n2];
      q[i].id = i;
   }//for
   sort(q, q + Q);
   L = 0; R = -1; tot = 0;
   for (int i = 0; i < Q; i++) {
      while (R < q[i].r) {
         if (!flag[P[++R]])
            tot += (++counter[A[P[R]]] == 1);
         else
            tot -= (--counter[A[P[R]]] == 0);
         flag[P[R]] = !flag[P[R]];
      }//while
      while (R > q[i].r) {
         if (!flag[P[R]])
            tot += (++counter[A[P[R]]] == 1);
         else
            tot -= (--counter[A[P[R]]] == 0);
         flag[P[R]] = !flag[P[R]];
         R--;
      }//while
      while (L < q[i].l) {
         if (!flag[P[L]])
            tot += (++counter[A[P[L]]] == 1);
         else
            tot -= (--counter[A[P[L]]] == 0);
         flag[P[L]] = !flag[P[L]];
         L++;
      }//while
      while (L > q[i].l) {
         if (!flag[P[--L]])
            tot += (++counter[A[P[L]]] == 1);
         else
            tot -= (--counter[A[P[L]]] == 0);
         flag[P[L]] = !flag[P[L]];
      }//while
      res[q[i].id] = tot + (q[i].p != P[q[i].l] && !counter[A[q[i].p]]);
   }//for
   for (int i = 0; i < Q; i++)
      printf("%d\n", res[i]);
   return 0;
}//main
