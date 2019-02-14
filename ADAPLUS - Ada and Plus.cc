#include <bits/stdc++.h>
using namespace std;

int l[2020][2020], r[2020][2020], u[2020][2020], d[2020][2020];
char grid[2020][2020];

int main() {
   int T, N, ans;
   scanf("%d", &T);
   while (T--) {
      scanf("%d", &N);
      for (int i = 1; i <= N; i++)
         scanf(" %s", 1 + grid[i]);
      for (int i = 1; i <= N + 1; i++)
         r[N + 1][i] = r[i][N + 1] = d[N + 1][i] = d[i][N + 1] = 0;
      for (int i = 1; i <= N; i++) {
         for (int j = 1; j <= N; j++) {
            l[i][j] = (grid[i][j] == '.') ? 0 : l[i][j - 1] + 1;
            u[i][j] = (grid[i][j] == '.') ? 0 : u[i - 1][j] + 1;
            r[i][N - j + 1] = (grid[i][N - j + 1] == '.') ? 0 : r[i][N - j + 2] + 1;
            d[N - i + 1][j] = (grid[N - i + 1][j] == '.') ? 0 : d[N - i + 2][j] + 1;
         }//for
      }//for
      ans = 0;
      for (int i = 1; i <= N; i++)
         for (int j = 1; j <= N; j++)
            ans = max(ans, min(min(l[i][j], r[i][j]), min(u[i][j], d[i][j])));
      printf("%d\n", ans);
   }//while
   return 0;
}//main
