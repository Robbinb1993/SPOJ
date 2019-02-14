#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 1 << 30;
const int MAXN = 600000;

int N;
int S[MAXN];
char M[MAXN];
map<int, int> to[MAXN];
int len[MAXN], start[MAXN], link[MAXN];
int node;
int pos;
int id, n;
string curr;
int mx;
LL res[26];

int makeNode (const int p, const int l) {
   start[id] = p;
   len[id] = l;
   return id++;
}//makeNode

void walkdown() {
   while (pos > len[to[node][S[n - pos]]]) {
      node = to[node][S[n - pos]];
      pos -= len[node];
   }//while
}//goEdge

void addLetter(const int c) {
   int last = 0, split, leaf;
   S[n++] = c;
   pos++;
   while (pos) {
      walkdown();
      int edge = S[n - pos];
      int& v = to[node][edge];
      int t = S[start[v] + pos - 1];
      if (!v) { //no path starting with this char
         v = makeNode(n - pos, INF);
         link[last] = node;
         last = node;
      }//if
      else if (t == c) {
         link[last] = node;
         return;
      }//else if
      else {
         int u = makeNode(start[v], pos - 1);
         to[u][c] = makeNode(n - 1, INF);
         to[u][t] = v;
         start[v] += pos - 1;
         if (len[v] != INF)
            len[v] -= pos - 1;
         v = u; //u is the split point
         link[last] = u;
         last = u;
      }//else
      if (!node) //node is the root
         pos--;
      else
         node = link[node]; //follow the suffix link from αx to x
   }//while
}//addLetter

LL DFS(const int u) {
   if (!u)
      return 0;
   if (len[u] == INF)
      return n - start[u] - 1;
   LL res = len[u];
   for (auto it = to[u].begin(); it != to[u].end(); it++) {
      if (it->first == '$')
         continue;
      res += DFS(it->second);
   }//if
   return res;
}//DFS

void init() {
   len[0] = INF;
   id = 1;
}//init

int main() {
   int T, L;
   init();
   scanf(" %s", M);
   L = strlen(M);
   for (int j = 0; j < L; j++)
      addLetter(M[j]);
   addLetter('$');
   for (int i = 0; i < 26; i++) {
      if (i)
         printf(" ");
      printf("%lld", DFS(to[0]['a' + i]));
   }//for
   puts("");
   return 0;
}//main
