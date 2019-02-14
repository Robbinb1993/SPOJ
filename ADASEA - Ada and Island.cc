#include "stdio.h"
#include <iostream>
#include <vector>
using namespace std;
const int nx[4] = {-1, 0, 1, 0};
const int ny[4] = {0, 1, 0, -1};
int w, h;
string m[1010];
vector<int> islands;

int gcd(long long int a, long long int b) {
   return b ? gcd(b, a % b) : a;
}

int floodfill(const int y, const int x) {
   int neighbours = 0;
   if (x < 0 || y < 0 || x >= w || y >= h || m[y][x] != '#')
      return 0;
   m[y][x] = '.';
   for (int i = 0; i < 4; i++)
      neighbours += floodfill(y + ny[i], x + nx[i]);
   return 1 + neighbours;
}//floodfill

int main() {
   int T;
   int div;
   int msize;
   long long int res, sum;
   scanf("%d", &T);
   while (T--) {
      scanf("%d %d", &h, &w);
      getline(cin, m[0]);
      for (int i = 0; i < h; i++)
         getline(cin, m[i]);
      sum = 0;
      for (int i = 0; i < h; i++) {
         for (int j = 0; j < w; j++) {
            if (m[i][j] == '#') {
               res = floodfill(i, j);
               sum += res * res;
            }//if
         }//for
      }//for
      msize = w * h;
      div = gcd(sum, msize);
      sum /= div;
      msize /= div;
      if (msize == 1)
         printf("%lld\n", sum);
      else
         printf("%lld / %d\n", sum, msize);
   }//while
   return 0;
}//main
