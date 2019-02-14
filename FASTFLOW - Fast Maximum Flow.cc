#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Edge {
   int to;
   LL rem;
   int rev;
};

const LL INF = 1000000000000000000;
vector<vector<Edge> > edges;
int level[5010];
int pos[5010];

int s, t;

bool BFS() {
   queue<int> Q;
   int curr;
   Q.push(s);
   memset(level, 0, sizeof(level));
   level[s] = 1;
   while (!Q.empty()) {
      curr = Q.front();
      Q.pop();
      for (int i = 0; i < (int)edges[curr].size(); i++) {
         if (level[edges[curr][i].to] == 0 && edges[curr][i].rem) {
            level[edges[curr][i].to] = level[curr] + 1;
            if (edges[curr][i].to == t)
               return true;
            Q.push(edges[curr][i].to);
         }//if
      }//for
   }//while
   return false;
}//BFS

LL DFS(const int curr, const LL flow) {
   if (curr == t)
      return flow;
   LL remflow = flow;
   LL totflow = 0;
   LL sent;
   for (; pos[curr] < (int)edges[curr].size(); pos[curr]++) {
      if (level[edges[curr][pos[curr]].to] == level[curr] + 1 && edges[curr][pos[curr]].rem) {
         sent = DFS(edges[curr][pos[curr]].to, min(remflow, edges[curr][pos[curr]].rem));
         edges[curr][pos[curr]].rem -= sent;
         edges[edges[curr][pos[curr]].to][edges[curr][pos[curr]].rev].rem += sent;
         remflow -= sent;
         totflow += sent;
         if (!remflow)
            break;
      }//if
   }//for
   return totflow;
}//DFS

void addEdge(const int id1, const int id2, const LL cap) {
   Edge e1, e2;
   e1.to = id2;
   e1.rem = cap;
   edges[id1].push_back(e1);
   e2.to = id1;
   e2.rem = 0;
   edges[id2].push_back(e2);
   edges[id1].back().rev = (int)edges[id2].size() - 1;
   edges[id2].back().rev = (int)edges[id1].size() - 1;
}//addEdge

LL Dinic() {
   LL mf = 0;
   while (BFS()) {
      memset(pos, 0, sizeof(pos));
      mf += DFS(s, INF);
   }//while
   return mf;
}//Dinic

template <typename T>
void fr(T& to) {
   char t; to ^= to;
   while (!isdigit((t = getchar_unlocked())));
   while (t > 47) { to = (to << 3) + (to << 1) + t - 48; t = getchar_unlocked(); }
}//fr

int main() {
   s = 0;
   int n, m, n1, n2, w;
   fr(n); fr(m);
   edges = vector<vector<Edge> >(n + 5);
   t = n + 4;
   addEdge(s, 1, INF);
   for (int i = 0; i < m; i++) {
      fr(n1); fr(n2); fr(w);
      addEdge(n1, n2, w);
      addEdge(n2, n1, w);
   }//for
   addEdge(n, t, INF);
   printf("%lld\n", Dinic());
   return 0;
}//main
