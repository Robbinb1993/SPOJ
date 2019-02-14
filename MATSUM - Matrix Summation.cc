#include <bits/stdc++.h>
using namespace std;

int N;
int A[1030][1030];
int S[1030][1030];

int sum(int x, const int y) {
   int s = 0;
   while (x) {
      int cy = y;
      while (cy)
         s += S[x][cy], cy -= (cy & -cy);
      x -= (x & -x);
   }//while
   return s;
}//sum

void update(int x, const int y, const int v, const int prv) {
   while (x <= N) {
      int cy = y;
      while (cy <= N)
         S[x][cy] += v - prv, cy += (cy & -cy);
      x += (x & -x);
   }//while
}//update

int RQ(const int x1, const int y1, const int x2, const int y2) {
   return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}//RQ

int main() {
   char com[10];
   int T, v, Q, x, y, x2, y2;
   scanf("%d", &T);
   while (T--) {
      scanf("%d", &N);
      memset(A, 0, sizeof(A));
      memset(S, 0, sizeof(S));
      while (scanf(" %s", com) == 1) {
         if (com[0] == 'E')
            break;
         else if (com[1] == 'E') {
            scanf("%d %d %d", &x, &y, &v);
            update(x + 1, y + 1, v, A[x][y]);
            A[x][y] = v;
         }//else if
         else {
            scanf("%d %d %d %d", &x, &y, &x2, &y2);
            printf("%d\n", RQ(x + 1, y + 1, x2 + 1, y2 + 1));
         }//else
      }//else
      puts("");
   }//while
   return 0;
}//main
