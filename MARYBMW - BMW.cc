#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, LL> iLL;
typedef pair<LL, int> LLi;
typedef vector<iLL> viLL;
typedef vector<viLL> vviLL;
const LL INF = 1000000000000000001;

vviLL edges;
int N;
LL dist[50050];

LL Dijkstra() {
   priority_queue<LLi, vector<LLi>> Q;
   Q.push(LLi(INF, 1));
   LLi curr;
   LL speed;
   dist[1] = INF;
   for (int i = 2; i <= N; i++)
      dist[i] = 0;
   while (!Q.empty()) {
      curr = Q.top();
      Q.pop();
      if (dist[curr.second] > curr.first)
         continue;
      if (curr.second == N)
         return curr.first;
      for (auto& e : edges[curr.second]) {
         speed = min(e.second, curr.first);
         if (speed > dist[e.first]) {
            dist[e.first] = speed;
            Q.push(LLi(speed, e.first));
         }//if
      }//for
   }//while
   return -1;
}//Dijkstra

template <typename T>
void fr(T& to) {
   char t; to ^= to;
   while (!isdigit((t = getchar_unlocked())));
   while (t > 47) { to = (to << 3) + (to << 1) + t - 48; t = getchar_unlocked(); }
}//fr

int main() {
   int T, E, n1, n2;
   LL L, M, R, res, w, mx;
   fr(T);
   while (T--) {
      fr(N); fr(E);
      mx = 0;
      edges.assign(N + 5, viLL());
      while (E--) {
         fr(n1); fr(n2); fr(w);
         edges[n1].push_back(iLL(n2, w));
         edges[n2].push_back(iLL(n1, w));
         mx = max(mx, w);
      }//while
      printf("%lld\n", Dijkstra());
   }//while
   return 0;
}//main
