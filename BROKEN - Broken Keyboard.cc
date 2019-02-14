#include <bits/stdc++.h>
using namespace std;

int counter[300];
int diff;
int L;

int main() {
   int T, m, len, mx;
   char S[1000010];
   while (scanf("%d", &m) && m) {
      fgets(S, sizeof(S), stdin);
      fgets(S, sizeof(S), stdin);
      memset(counter, 0, sizeof(counter));
      mx = L = diff = 0;
      len = strlen(S);
      for (int i = 0; i < len - 1; i++) {
         if (++counter[S[i]] == 1)
            diff++;
         while (diff > m) {
            if (--counter[S[L++]] == 0)
               diff--;
         }//while
         mx = max(mx, i - L + 1);
      }//for
      printf("%d\n", mx);
   }//while
   return 0;
}//main
