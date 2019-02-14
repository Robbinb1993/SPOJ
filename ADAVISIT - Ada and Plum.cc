#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;

int N;
int HLDid[400010];
int pos[400010];
int treeSize[400010];
int segSize[400010];
int root[400010];
int parent[400010];
int HID = 0;
int D[400010];
vvi edges, segTrees;

int query(const int id, const int p, const int L, const int R, const int idx) {
   if (L != R) {
      segTrees[id][idx << 1] += segTrees[id][idx];
      segTrees[id][(idx << 1) + 1] += segTrees[id][idx];
      segTrees[id][idx] = 0;
   }//if
   else
      return segTrees[id][idx];
   int M = (L + R) >> 1;
   if (p <= M)
      return query(id, p, L, M, idx << 1);
   else
      return query(id, p, M + 1, R, (idx << 1) + 1);
}//query

void update(const int id, const int l, const int r, const int L, const int R, const int idx) {
   if (L >= l && R <= r) {
      segTrees[id][idx]++;
      return;
   }//if
   int M = (L + R) >> 1;
   if (l <= M)
      update(id, l, r, L, M, idx << 1);
   if (r > M)
      update(id, l, r, M + 1, R, (idx << 1) + 1);
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
   pos[u] = sz;
   int mx = 0, nxt;
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
      segSize[id] = sz;
      while ((int)segTrees.size() < id + 1)
         segTrees.push_back(vector<int>());
      segTrees[id].assign(sz << 2, 0);
   }//if
}//DFS1

int main() {
   int n1, n2, curr;
   scanf("%d", &N);
   edges.assign(N + 5, vector<int>());
   for (int i = 0; i < N - 1; i++) {
      scanf("%d %d", &n1, &n2);
      edges[n1].push_back(n2);
      edges[n2].push_back(n1);
   }//for
   DFS(1, 1, 0);
   DFS1(1, 1, 0, 1);
   curr = 1;
   while (curr != N) {
      n1 = curr; n2 = curr + 1;
      while (HLDid[n1] != HLDid[n2]) {
         if (D[root[HLDid[n1]]] >= D[root[HLDid[n2]]]) {
            update(HLDid[n1], 1, pos[n1], 1, segSize[HLDid[n1]], 1);
            n1 = parent[root[HLDid[n1]]];
         }//while
         else {
            update(HLDid[n2], 1, pos[n2], 1, segSize[HLDid[n2]], 1);
            n2 = parent[root[HLDid[n2]]];
         }//else
      }//while
      if (pos[n1] > pos[n2])
         swap(n1, n2);
      update(HLDid[n1], pos[n1], pos[n2], 1, segSize[HLDid[n2]], 1);
      curr++;
   }//while
   for (int i = 1; i <= N; i++)
      printf("%d\n", query(HLDid[i], pos[i], 1, segSize[HLDid[i]], 1));
   return 0;
}//main
