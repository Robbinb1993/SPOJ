#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50010;

int N, bs;
deque<int> D[2 * MAXN];
int A[MAXN], res[MAXN];
map<int, int> counter;

struct Q {
   int l, r, id;
   bool operator < (const Q& other) const {
      return (l / bs < other.l / bs || (l / bs == other.l / bs && r < other.r));
   }//operator <
} q[MAXN];

int main() {
   int Q;
   scanf("%d %d", &N, &Q);
   bs = sqrt(N);
   for (int i = 0; i < N; i++)
      scanf("%d", &A[i]);
   for (int i = 0; i < Q; i++) {
      scanf("%d %d", &q[i].l, &q[i].r);
      q[i].l--; q[i].r;
      q[i].id = i;
   }//for
   sort(q, q + Q);
   int L = 0, R = -1, sumL = 0, sumR = 0;
   for (int i = 0; i < Q; i++) {
      while (R < q[i].r) {
         if ((int)D[sumR + N].size() > 1) {
            auto it = counter.find(D[sumR + N].back() - D[sumR + N].front());
            if (it != counter.end()) {
               if (it->second == 1)
                  counter.erase(it);
               else
                  it->second--;
            }//if
         }//if
         D[sumR + N].push_back(++R);
         counter[D[sumR + N].back() - D[sumR + N].front()]++;
         sumR += A[R];
      }//while
      while (R > q[i].r) {
         sumR -= A[R--];
         auto it = counter.find(D[sumR + N].back() - D[sumR + N].front());
         if (it != counter.end()) {
            if (it->second == 1)
               counter.erase(it);
            else
               it->second--;
         }//if
         D[sumR + N].pop_back();
         if ((int)D[sumR + N].size() > 1)
            counter[D[sumR + N].back() - D[sumR + N].front()]++;
      }//while
      while (L < q[i].l) {
         auto it = counter.find(D[sumL + N].back() - D[sumL + N].front());
         if (it != counter.end()) {
            if (it->second == 1)
               counter.erase(it);
            else
               it->second--;
         }//if
         D[sumL + N].pop_front();
         if ((int)D[sumL + N].size() > 1)
            counter[D[sumL + N].back() - D[sumL + N].front()]++;
         sumL += A[L++];
      }//while
      while (L > q[i].l) {
         sumL -= A[--L];
         if ((int)D[sumL + N].size() > 1) {
            auto it = counter.find(D[sumL + N].back() - D[sumL + N].front());
            if (it != counter.end()) {
               if (it->second == 1)
                  counter.erase(it);
               else
                  it->second--;
            }//if
         }//if
         D[sumL + N].push_front(L);
         counter[D[sumL + N].back() - D[sumL + N].front()]++;
      }//while
      if (!counter.empty())
         res[q[i].id] = counter.rbegin()->first;
   }//for
   for (int i = 0; i < Q; i++)
      printf("%d\n", res[i]);
   return 0;
}//main
