#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int N, M, Q;
int A[2020][2020];
LL sum[2040][2040];
LL V[8040][8040];

void build2(const int l, const int r, const int id, const int L = 1, const int R = M, const int idx = 1) {
   if (L == R) {
      V[id][idx] = sum[r][L] - sum[l - 1][L];
      return;
   }//if
   int M = (L + R) >> 1;
   build2(l, r, id, L, M, idx << 1);
   build2(l, r, id, M + 1, R, (idx << 1) + 1);
   V[id][idx] = V[id][idx << 1] + V[id][(idx << 1) + 1];
}//build2

void build1(const int L = 1, const int R = N, const int idx = 1) {
   build2(L, R, idx);
   if (L == R)
      return;
   int M = (L + R) >> 1;
   build1(L, M, idx << 1);
   build1(M + 1, R, (idx << 1) + 1);
}//build1

void update2(const int c, const int v, const int id, const int L = 1, const int R = M, const int idx = 1) {
   V[id][idx] += v;
   if (L == R)
      return;
   int M = (L + R) >> 1;
   if (c <= M)
      update2(c, v, id, L, M, idx << 1);
   else
      update2(c, v, id, M + 1, R, (idx << 1) + 1);
}//update2

void update1(const int r, const int c, const int v, const int L = 1, const int R = N, const int idx = 1) {
   update2(c, v, idx);
   if (L == R)
      return;
   int M = (L + R) >> 1;
   if (r <= M)
      update1(r, c, v, L, M, idx << 1);
   else
      update1(r, c, v, M + 1, R, (idx << 1) + 1);
}//update1

LL query2(const int c1, const int c2, const int id, const int L = 1, const int R = M, const int idx = 1) {
   if (L >= c1 && R <= c2)
      return V[id][idx];
   int M = (L + R) >> 1;
   LL res = 0;
   if (c1 <= M)
      res += query2(c1, c2, id, L, M, idx << 1);
   if (c2 > M)
      res += query2(c1, c2, id, M + 1, R, (idx << 1) + 1);
   return res;
}//query2

LL query1(const int r1, const int r2, const int c1, const int c2, const int L = 1, const int R = N, const int idx = 1) {
   if (L >= r1 && R <= r2)
      return query2(c1, c2, idx);
   int M = (L + R) >> 1;
   LL res = 0;
   if (r1 <= M)
      res += query1(r1, r2, c1, c2, L, M, idx << 1);
   if (r2 > M)
      res += query1(r1, r2, c1, c2, M + 1, R, (idx << 1) + 1);
   return res;
}//query1

int main() {
   ios::sync_with_stdio(false);
   int t, r1, c1, r2, c2, v;
   cin >> N >> M >> Q;
   for (int i = 1; i <= N; i++)
      for (int j = 1; j <= M; j++)
         cin >> A[i][j], sum[i][j] = A[i][j] + sum[i - 1][j];
   build1();
   while (Q--) {
      cin >> t;
      if (t == 1) {
         cin >> r1 >> c1 >> v;
         update1(r1, c1, v);
      }//if
      else {
         cin >> r1 >> c1 >> r2 >> c2;
         cout << query1(r1, r2, c1, c2) << "\n";
      }//else
   }//while
   return 0;
}//main
