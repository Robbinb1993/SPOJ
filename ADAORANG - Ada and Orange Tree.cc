#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
int LOGN;

int N;
int level[500000];
int DP[20][500000];
int col[500000];
vvi edges;
bool seen[500000];
bitset<255> colors[500000];

void DFS0(const int u) {
   seen[u] = 1;
   colors[u] = 0;
   colors[u].set(col[u]);
   for (auto& e : edges[u]) {
      if (!seen[e]) {
         DP[0][e] = u;
         level[e] = level[u] + 1;
         DFS0(e);
         colors[u] |= colors[e];
      }//if
   }//for
}//DFS0

void prep(const int r) {
   memset(seen, 0, sizeof(seen));
   level[r] = 0;
   for (int i = 0; i < LOGN; i++)
      DP[i][r] = r;
   DFS0(r);
   for (int i = 1; i < LOGN; i++)
      for (int j = 0; j < N; j++)
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

void fr(int &to) {
   char t; to ^= to;
   while (!isdigit((t = getchar())));
   while (t > 47) { to = (to << 3) + (to << 1) + t - 48; t = getchar(); }
}//fr

int main() {
   int T, Q, R, n1, n2, lca;
   fr(T);
   while (T--) {
      fr(N); fr(Q); fr(R);
      for (int i = 1; ; i++) {
         if ((1 << i) > N) {
            LOGN = i;
            break;
         }//if
      }//for
      edges.assign(N + 5, vi());
      for (int i = 0; i < N; i++)
         fr(col[i]);
      for (int i = 0; i < N - 1; i++) {
         fr(n1); fr(n2);
         edges[n1].push_back(n2);
         edges[n2].push_back(n1);
      }//for
      prep(R);
      while (Q--) {
         fr(n1); fr(n2);
         lca = LCA(n1, n2);
         printf("%d\n", colors[lca].count());
      }//while
   }//while
   return 0;
}//main
