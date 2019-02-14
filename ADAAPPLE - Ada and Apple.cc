#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;

int N, Q;
char temp[300010];
int type[300010];
int HLDid[300010];
int pos[300010];
int treeSize[300010];
int segSize[300010];
int root[300010];
int parent[300010];
int HID = 0;
int D[300010];
vvi edges, segTrees;

int query(const int id, const int l, const int r, const int L, const int R, const int idx) {
   if (L >= l && R <= r)
      return segTrees[id][idx];
   int M = (L + R) >> 1;
   int res = 0;
   if (l <= M)
      res += query(id, l, r, L, M, idx << 1);
   if (r > M)
      res += query(id, l, r, M + 1, R, (idx << 1) + 1);
   return res;
}//query

void update(const int id, const int p, const int v, const int L, const int R, const int idx) {
   if (L == R) {
      segTrees[id][idx] = v;
      return;
   }//if
   int M = (L + R) >> 1;
   if (p <= M)
      update(id, p, v, L, M, idx << 1);
   else
      update(id, p, v, M + 1, R, (idx << 1) + 1);
   segTrees[id][idx] = segTrees[id][idx << 1] + segTrees[id][(idx << 1) + 1];
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
      segSize[id] = sz - 1;
      while ((int)segTrees.size() < id + 1)
         segTrees.push_back(vector<int>());
      segTrees[id].assign(sz << 2, 0);
   }//if
   update(id, pos[u], type[u], 0, segSize[id], 1);
}//DFS1

int main() {
   int n1, n2, t, p, sum, counter;
   scanf("%d %d", &N, &Q);
   scanf(" %s", temp);
   for (int i = 0; i < N; i++)
      type[i] = temp[i] - '0';
   edges.assign(N + 5, vector<int>());
   for (int i = 0; i < N - 1; i++) {
      scanf("%d %d", &n1, &n2);
      edges[n1].push_back(n2);
      edges[n2].push_back(n1);
   }//for
   DFS(0, 0, 0);
   DFS1(0, 0, 0, 1);
   while (Q--) {
      scanf("%d", &t);
      if (t == 0) {
         scanf("%d", &p);
         type[p] = !type[p];
         update(HLDid[p], pos[p], type[p], 0, segSize[HLDid[p]], 1);
      }//if
      else {
         scanf("%d %d", &n1, &n2);
         sum = counter = 0;
         while (HLDid[n1] != HLDid[n2] && (!sum || sum == counter)) {
            if (D[root[HLDid[n1]]] >= D[root[HLDid[n2]]]) {
               counter += pos[n1] + 1;
               sum += query(HLDid[n1], 0, pos[n1], 0, segSize[HLDid[n1]], 1);
               n1 = parent[root[HLDid[n1]]];
            }//while
            else {
               counter += pos[n2] + 1;
               sum += query(HLDid[n2], 0, pos[n2], 0, segSize[HLDid[n2]], 1);
               n2 = parent[root[HLDid[n2]]];
            }//else
         }//while

         if (sum && sum != counter) {
            puts("NO");
            continue;
         }//if
         if (pos[n1] > pos[n2])
            swap(n1, n2);

         counter += pos[n2] - pos[n1] + 1;
         sum += query(HLDid[n1], pos[n1], pos[n2], 0, segSize[HLDid[n1]], 1);
         if (sum && sum != counter)
            puts("NO");
         else
            puts("YES");
      }//else
   }//while
   return 0;
}//main
