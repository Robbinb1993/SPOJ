#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

int st[5050], ed[5050];
vector<int> luS[5050], luE[5050], rbS[5050], rbE[5050];
int rain[5050][5050];

int main() {
   int N, M, L;
   int x, y, X, Y, v;
   int crain;
   scanf("%d %d %d", &N, &M, &L);
   for (int i = 0; i < N; i++) {
      scanf("%d %d %d %d", &x, &y, &X, &Y);
      luS[x].push_back(y);
      luE[x].push_back(Y);
      rbS[X].push_back(y);
      rbE[X].push_back(Y);
   }//for
   crain = 0;
   for (int i = 1; i <= L; i++) {
      for (auto& e : luS[i])
         st[e]++;
      for (auto& e : luE[i])
         ed[e]++;
      for (int j = 1; j <= L; j++) {
         crain += st[j];
         rain[i][j] = crain;
         crain -= ed[j];
      }//for
      for (auto& e : rbS[i])
         st[e]--;
      for (auto& e : rbE[i])
         ed[e]--;
   }//for
   while (M--) {
      scanf("%d %d", &x, &y);
      printf("%d\n", rain[x][y]);
   }//while
   return 0;
}//main
