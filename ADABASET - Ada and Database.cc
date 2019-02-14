#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int D[15];
LL V[2000010];
int sum[15];

int main() {
   ios_base::sync_with_stdio(false);
   string in;
   int N, d, dim, loc, idx, T = 1;
   while (getline(cin, in) && (int)in.length()) {
      stringstream ss;
      dim = 0;
      ss << in;
      while (ss >> d)
         D[dim++] = d;
      N = 1;
      sum[dim - 1] = 1;
      for (int i = dim - 2; i >= 0; i--)
         sum[i] = sum[i + 1] * D[i + 1];
      for (int i = 0; i < dim; i++)
         N *= D[i];
      for (int i = 0; i < N; i++)
         cin >> V[i];
      getline(cin, in);
      getline(cin, in);
      stringstream ss2;
      ss2 << in;
      while (ss2 >> loc) {
         idx = sum[0] * --loc;
         for (int i = 1; i < dim; i++)
            ss2 >> loc, idx += sum[i] * --loc;
         cout << V[idx] << "\n";
      }//while
      for (int i = 0; i < T; i++)
         cout << "#";
      T++;
      cout << "\n";
   }//while
   return 0;
}//main
