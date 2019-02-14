#include <bits/stdc++.h>
using namespace std;

int s1, s2, s3, s4;

int cache[10000][101][2];

bool getWinner(const int c1, const int c2, const int c3, const int c4, const int moves, const bool Ada) {
   //convert string to int
   int configValue = c1 * 1000 + c2 * 100 + c3 * 10 + c4;
   int mem = cache[configValue][moves][Ada];
   if (mem == 0)
      return false;
   else if (mem == 1)
      return true;
   if (moves == 0) {
      if (configValue <= s1 * 1000 + s2 * 100 + s3 * 10 + s4) {
         cache[configValue][moves][Ada] = 0;
         return false;
      }//if
      else {
         cache[configValue][moves][Ada] = 1;
         return true;
      }//else
   }//if
   else {
      if (Ada) {
         if (getWinner((c1 + 1) % 10, c2, c3, c4, moves - 1, false) ||
             getWinner(c1, (c2 + 1) % 10, c3, c4, moves - 1, false) ||
             getWinner(c1, c2, (c3 + 1) % 10, c4, moves - 1, false) ||
             getWinner(c1, c2, c3, (c4 + 1) % 10, moves - 1, false)) {
            cache[configValue][moves][Ada] = 1;
            return true;
         }//if
         else {
            cache[configValue][moves][Ada] = 0;
            return false;
         }//else
      }//if
      else { //Vinits turn
         if (!getWinner((c1 + 1) % 10, c2, c3, c4, moves - 1, true) ||
             !getWinner(c1, (c2 + 1) % 10, c3, c4, moves - 1, true) ||
             !getWinner(c1, c2, (c3 + 1) % 10, c4, moves - 1, true) ||
             !getWinner(c1, c2, c3, (c4 + 1) % 10, moves - 1, true)) {
            cache[configValue][moves][Ada] = 0;
            return false;
         }//if
         else {
            cache[configValue][moves][Ada] = 1;
            return true;
         }//else
      }//else
   }//else
}//getWinner

int main() {
   int N;
   int moves;
   scanf("%d", &N);
   getchar();
   for (int i = 0; i < N; i++) {
      s1 = getchar() - '0';
      s2 = getchar() - '0';
      s3 = getchar() - '0';
      s4 = getchar() - '0';
      scanf("%d", &moves);
      getchar();
      memset(cache, -1, sizeof(cache));
      getWinner(s1, s2, s3, s4, moves, true) ? printf("Ada\n") : printf("Vinit\n");
   }//for
   return 0;
}//main
