#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1 << 30;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int N;
int grid[110][110];
int counter[15];
bool matched[10010];
int matching[10010];
int dist[10010];
vvi edges;

bool BFS(const int x) {
   queue<int> Q;
   bool flag = false;
   for (int i = 0; i < counter[x]; i++) {
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
      for (int r : edges[l]) {
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
   for (int r : edges[l]) {
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

int HopcroftKarp(const int x) {
   int mf = 0;
   while (BFS(x)) {
      for (int i = 0; i < counter[x]; i++) {
         if (!matched[i])
            mf += DFS(i);
      }//for
   }//while
   return mf;
}//HopcroftKarp


void setEdges(const int x, const int y, const int v) {
   int nx, ny;
   for (int i = 0; i < 4; i++) {
      nx = x + dx[i];
      ny = y + dy[i];
      if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] == grid[x][y] + 1)
         edges[v].push_back(nx * N + ny);
   }//for
}//setEdges

int main() {
   int T, until, v, nx, ny;
   bool valid;
   scanf("%d", &T);
   while (T--) {
      scanf("%d", &N);
      until = 0;
      memset(counter, 0, sizeof(counter));
      for (int i = 0; i < N; i++)
         for (int j = 0; j < N; j++)
            scanf("%d", &grid[i][j]), until = max(until, grid[i][j]), counter[grid[i][j]]++;
      valid = true;
      for (int i = 1; i < until; i++) {
         if (counter[i + 1] > counter[i]) {
            valid = false;
            break;
         }//if
      }//for
      for (int i = 0; i < N && valid; i++) {
         for (int j = 0; j < N && valid; j++) {
            if (grid[i][j] > 1) {
               for (int k = 0; k < 4; k++) {
                  nx = i + dx[k];
                  ny = j + dy[k];
                  if (nx >= 0  && nx < N && ny >= 0 && ny < N && grid[nx][ny] == grid[i][j] - 1)
                     break;
                  if (k == 3)
                     valid = false;
               }//for
            }//if
         }//for
      }//for
      for (int i = 1; i < until && valid; i++) {
         memset(matched, 0, sizeof(matched));
         memset(matching, -1, sizeof(matching));
         edges.assign(counter[i] + 5, vi());
         v = 0;
         for (int x = 0; x < N; x++)
            for (int y = 0; y < N; y++)
               if (grid[x][y] == i)
                  setEdges(x, y, v++);
         if (HopcroftKarp(i) != counter[i + 1])
            valid = false;
      }//for
      valid ? puts("YES") : puts("NO");
   }//while
   return 0;
}//main
