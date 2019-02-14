#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void fr(int &to) {
   char t; to ^= to;
   bool flag = false;
   while (!isdigit((t = getchar_unlocked()))) {
      if (t == '-')
         flag = 1;
   }//if
   while (t > 47) { to = (to << 3) + (to << 1) + t - 48; t = getchar_unlocked(); }
   if (flag) to = -to;
}//fr

int main() {
   int N, a;
   LL curr, prv, traded;
   while (true) {
      fr(N);
      if (!N)
         break;
      traded = prv = 0;
      for (int i = 0; i < N; i++) {
         fr(a);
         curr = prv + a;
         traded += abs(curr);
         prv = curr;
      }//for
      printf("%lld\n", traded);
   }//while
   return 0;
}//main
