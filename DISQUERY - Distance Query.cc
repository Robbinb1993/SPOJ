#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
const int SZ = 100010;
const int INF = 1 << 30;

int N, Q;
int HLDid[SZ];
int pos[SZ];
int treeSize[SZ];
int segSize[SZ];
int root[SZ];
int parent[SZ];
int D[SZ];
int HID = 0;
vector<int> segTreesMn[SZ], segTreesMx[SZ];
map<ii, int> w;
vvi edges;

ii query(const int id, const int l, const int r, const int L, const int R, const int idx = 1) {
   if (L >= l && R <= r)
      return ii(segTreesMn[id][idx], segTreesMx[id][idx]);
   int M = (L + R) >> 1;
   ii res = ii(INF, -1);
   if (l <= M)
      res = query(id, l, r, L, M, idx << 1);
   if (r > M) {
      ii ret = query(id, l, r, M + 1, R, (idx << 1) + 1);
      res.first = min(res.first, ret.first);
      res.second = max(res.second, ret.second);
   }//if
   return res;
}//query

void update(const int id, const int p, const int v, const int L, const int R, const int idx = 1) {
   if (L == R) {
      segTreesMn[id][idx] = v;
      segTreesMx[id][idx] = v == INF ? -INF : v;
      return;
   }//if
   int M = (L + R) >> 1;
   if (p <= M)
      update(id, p, v, L, M, idx << 1);
   else
      update(id, p, v, M + 1, R, (idx << 1) + 1);
   segTreesMn[id][idx] = min(segTreesMn[id][idx << 1], segTreesMn[id][(idx << 1) + 1]);
   segTreesMx[id][idx] = max(segTreesMx[id][idx << 1], segTreesMx[id][(idx << 1) + 1]);
}//update

int DFS(const int u, const int prev, const int depth) {
   D[u] = depth;
   parent[u] = prev;
   treeSize[u] = 1;
   for (auto& e : edges[u])
      if (e != prev)
         treeSize[u] += DFS(e, u, depth + 1);
   return treeSize[u];
}//DFS

void DFS1(const int u, const int prev, const int id, const int sz) {
   if (sz == 1)
      root[id] = u;
   HLDid[u] = id;
   pos[u] = sz - 1;
   int mx = 0, nxt = -1;
   for (auto& e : edges[u])
      if (e != prev && treeSize[e] > mx)
         mx = treeSize[e], nxt = e;
   bool flag = false;
   for (auto& e : edges[u]) {
      if (e != prev) {
         if (e == nxt)
            DFS1(e, u, id, sz + 1), flag = 1;
         else
            DFS1(e, u, ++HID, 1), flag = 1;
      }//if
   }//for
   if (!flag) {
      segSize[id] = sz - 1;
      segTreesMn[id].assign(sz << 2, 0);
      segTreesMx[id].assign(sz << 2, 0);
   }//if
   if (prev != u)
      update(id, pos[u], w[ii(prev, u)], 0, ((int)segTreesMn[id].size() >> 2) - 1);
}//DFS1

int main() {
   int n1, n2, l;
   scanf("%d", &N);
   edges.assign(N + 5, vector<int>());
   for (int i = 0; i < N - 1; i++) {
      scanf("%d %d %d", &n1, &n2, &l);
      n1--; n2--;
      edges[n1].push_back(n2);
      edges[n2].push_back(n1);
      w[ii(n1, n2)] = w[ii(n2, n1)] = l;
   }//for
   DFS(0, 0, 0);
   DFS1(0, 0, 0, 1);
   update(0, 0, INF, 0, ((int)segTreesMn[0].size() >> 2) - 1);
   scanf("%d", &Q);
   while (Q--) {
      scanf("%d %d", &n1, &n2);
      n1--; n2--;
      ii res = ii(INF, -1);
      while (HLDid[n1] != HLDid[n2]) {
         if (D[root[HLDid[n1]]] < D[root[HLDid[n2]]])
            swap(n1, n2);
         ii ret = query(HLDid[n1], 0, pos[n1], 0, ((int)segTreesMn[HLDid[n1]].size() >> 2) - 1);
         res.first = min(res.first, ret.first);
         res.second = max(res.second, ret.second);
         n1 = parent[root[HLDid[n1]]];
      }//while
      if (D[n1] < D[n2])
         swap(n1, n2);
      if (n1 != n2) {
         ii ret = query(HLDid[n1], pos[n2] + 1, pos[n1], 0, ((int)segTreesMn[HLDid[n1]].size() >> 2) - 1);
         res.first = min(res.first, ret.first);
         res.second = max(res.second, ret.second);
      }//if
      printf("%d %d\n", res.first, res.second);
   }//while
   return 0;
}//main
