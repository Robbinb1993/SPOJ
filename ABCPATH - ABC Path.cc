#include <bits/stdc++.h>
using namespace std;

char table[55][55];
int DP[55][55];
int R, C;

const int nx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int ny[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const string sentence = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";

int DFS(const int i, const int j, const int idx) {
   if (table[i][j] != sentence[idx])
      return idx;
   if (DP[i][j] != -1)
      return DP[i][j];
   int result = 1;
   for (int k = 0; k < 8; k++) {
      if (i + nx[k] < 0 || i + nx[k] >= R || j + ny[k] < 0 || j + ny[k] >= C)
         continue;
      result = max(result, DFS(i + nx[k], j + ny[k], idx + 1));
   }//for
   return DP[i][j] = result;
}//DFS

int main() {
   int Case = 1;
   int result;
   while (true) {
      scanf("%d %d", &R, &C);
      if (R + C == 0)
         return 0;
      result = 0;
      memset(DP, -1, sizeof(DP));
      for (int i = 0; i < R; i++)
         scanf("%s", table[i]);
      for (int i = 0; i < R; i++)
         for (int j = 0; j < C; j++)
            result = max(result, DFS(i, j, 0));
      printf("Case %d: %d\n", Case++, result);
   }//while
}//main
