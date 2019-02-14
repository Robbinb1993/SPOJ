#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int id = 1;
map<int, int> getID;
map<int, int>::iterator it;

int bs;
int passed[200010];
int counter[200010];
int amount[200010];
int A[200010];
LL res[200010];

struct Q {
   int l, r, id;
   bool operator < (const Q& other) const {
      return (l / bs < other.l / bs || (l / bs == other.l / bs && r < other.r));
   }//operator <
} q[200010];

int main() {
   int N, Q, a, tot, curr, num;
   int L = 0, R = -1;
   LL sum = 0;
   scanf("%d %d", &N, &Q);
   bs = sqrt(N);
   for (int i = 0; i < N; i++) {
      scanf("%d", &a);
      A[i] = ((it = getID.find(a)) != getID.end()) ? it->second : (getID[a] = id++);
   }//for
   for (int i = 0; i < Q; i++) {
      scanf("%d %d", &q[i].l, &q[i].r);
      q[i].l--; q[i].r--;
      q[i].id = i;
   }//for
   sort(q, q + Q);
   for (int i = 0; i < Q; i++) {
      while (R < q[i].r) {
         counter[amount[A[++R]]]--;
         passed[++amount[A[R]]]++;
         counter[amount[A[R]]]++;
         sum += passed[amount[A[R]]];
      }//while
      while (R > q[i].r) {
         sum -= passed[amount[A[R]]]--;
         counter[amount[A[R]]]--;
         counter[--amount[A[R]]]++;
         R--;
      }//while
      while (L < q[i].l) {
         sum -= passed[amount[A[L]]]--;
         counter[amount[A[L]]]--;
         counter[--amount[A[L]]]++;
         L++;
      }//while
      while (L > q[i].l) {
         counter[amount[A[--L]]]--;
         passed[++amount[A[L]]]++;
         counter[amount[A[L]]]++;
         sum += passed[amount[A[L]]];
      }//while
      res[q[i].id] = sum;
   }//for

   for (int i = 0; i < Q; i++)
      printf("%lld\n", res[i]);
   return 0;
}//main
