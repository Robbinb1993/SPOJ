#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int INF = 1 << 30;

int N, M, F, T;
int H[510];
int w[510][510];
int dist[510];
bool matched[510];
int matching[510];
vvi edges, edges2, edges3;

bool BFS() {
   queue<int> Q;
   bool flag = false;
   for (int i = 0; i < (int)edges3.size(); i++) {
      if (!matched[i]) {
         Q.push(i);
         dist[i] = 0;
      }//if
      else
         dist[i] = INF;
   }//for

   while (!Q.empty()) {
      int l = Q.front();
      Q.pop();
      for (int r : edges3[l]) {
         if (matching[r] != -1) {
            if (dist[matching[r]] == INF) {
               dist[matching[r]] = dist[l] + 1;
               Q.push(matching[r]);
            }//if
         }//if
         else
            flag = true;
      }//for
   }//while
   return flag;
}//BFS

bool DFS(const int l) {
   for (int r : edges3[l]) {
      if (matching[r] == -1) {
         matched[l] = 1;
         matching[r] = l;
         return true;
      }//if
      if (dist[matching[r]] == dist[l] + 1) {
         if (DFS(matching[r])) {
            matched[l] = 1;
            matching[r] = l;
            return true;
         }//if
      }//if
   }//for
   dist[l] = INF;
   return false;
}//DFS

int HopcroftKarp() {
   int mf = 0;
   while (BFS()) {
      for (int i = 0; i < (int)edges3.size(); i++) {
         if (!matched[i])
            mf += DFS(i);
      }//for
   }//while
   return mf;
}//HopcroftKarp

void Dijkstra(const int s) {
   priority_queue<ii, vector<ii>, greater<ii>> Q;
   Q.push(ii(0, s));
   for (int i = 1; i <= N; i++)
      dist[i] = INF;
   dist[s] = 0;
   ii curr;
   while (!Q.empty()) {
      curr = Q.top();
      if (curr.first > T)
         return;
      Q.pop();
      edges2[s].push_back(curr.second);
      if (dist[curr.second] < curr.first)
         continue;
      for (auto& it : edges[curr.second]) {
         if (curr.first + w[curr.second][it] < dist[it]) {
            dist[it] = curr.first + w[curr.second][it];
            Q.push(ii(dist[it], it));
         }//if
      }//for
   }//while
}//Dijkstra

int main() {
   int t, A, B, L;
   scanf("%d", &t);
   while (t--) {
      scanf("%d %d %d %d", &N, &M, &F, &T);
      edges.assign(N + 5, vi());
      edges2.assign(N + 5, vi());
      edges3.assign(F + 5, vi());
      for (int i = 0; i < F; i++)
         scanf("%d", &H[i]);
      for (int i = 1; i <= N; i++)
         for (int j = 1; j <= N; j++)
            w[i][j] = INF;
      while (M--) {
         scanf("%d %d %d", &A, &B, &L);
         if (w[A][B] == INF) {
            edges[A].push_back(B);
            edges[B].push_back(A);
         }//if
         w[A][B] = w[B][A] = min(w[A][B], L);
      }//while
      sort(H, H + F);
      for (int i = 0; i < F; i++)
         if (i == 0 || H[i] != H[i - 1])
            Dijkstra(H[i]);
      for (int i = 0; i < F; i++)
            edges3[i] = edges2[H[i]];
      memset(matched, 0, sizeof(matched));
      memset(matching, -1, sizeof(matching));
      printf("%d\n", HopcroftKarp());
   }//while
   return 0;
}//main
