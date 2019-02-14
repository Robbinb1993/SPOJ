#include <bits/stdc++.h>
using namespace std;

int N;
int DP[2][2];

int main() {
   int prvX = 0, prvY = 0, currX, currY;
   bool flag = 0;
   scanf("%d", &N);
   for (int i = 0; i < N; i++) {
      scanf("%d %d", &currX, &currY);
      DP[0][flag] = max(DP[0][!flag] + (i ? abs(prvY - currY) : 0) + currX, DP[1][!flag] + (i ? abs(prvX - currY) : 0) + currX);
      DP[1][flag] = max(DP[0][!flag] + (i ? abs(prvY - currX) : 0) + currY, DP[1][!flag] + (i ? abs(prvX - currX) : 0) + currY);
      flag = !flag, prvX = currX, prvY = currY;
   }//while
   printf("%d\n", max(DP[0][!flag], DP[1][!flag]));
   return 0;
}//main
