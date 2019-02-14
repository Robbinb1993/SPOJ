#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int seen[1000010];
vvi edges;

bool BFS(const int K, const int S, const int id) {
   if (seen[K])
      return false;
   seen[K] = id;
   queue<int> Q;
   Q.push(K);
   int curr, until;
   for (int i = 0; i < S; i++) {
      until = (int)Q.size();
      while (until--) {
         curr = Q.front();
         Q.pop();
         for (auto& e : edges[curr]) {
            if (seen[e] && seen[e] != id)
               return false;
            else if (!seen[e])
               Q.push(e), seen[e] = id;
         }//for
      }//while
   }//for
   return true;
}//BFS

int main() {
   int T, N, R, M, n1, n2, k, s;
   bool valid;
   scanf("%d", &T);
   while (T--) {
      scanf("%d %d %d", &N, &R, &M);
      edges.assign(N + 5, vi());
      memset(seen, 0, sizeof(int) * (N + 5));
      while (R--) {
         scanf("%d %d", &n1, &n2);
         edges[n1].push_back(n2);
         edges[n2].push_back(n1);
      }//while
      valid = true;
      for (int i = 1; i <= M; i++) {
         scanf("%d %d", &k, &s);
         if (valid)
            valid = BFS(k, s, i);
      }//for
      for (int i = 1; i <= N && valid; i++)
         if (!seen[i])
            valid = false;
      valid ? puts("Yes") : puts("No");
   }//while
   return 0;
}//main
