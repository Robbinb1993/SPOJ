#include <bits/stdc++.h>
using namespace std;
typedef complex<double> Complex;
typedef vector<Complex> VC;

const double eps = 1e-3;
const double PI = acos(-1);

char S[500010], T[500010];
string DNA = "ACTG";
vector<int> pw2;

void fft(VC& f, const int dir = 1) {
   int n = (int)f.size();
   complex<double> r, w, u, v;
   double theta;

   for (int i = 1, j = 0; i < (int)f.size(); ++i) {
      int bit = n >> 1;
      while (j >= bit) {
         j -= bit;
         bit >>= 1;
      }//while
      j += bit;
      if (i < j)
         swap(f[i], f[j]);
   }//for

   for (int l = 1; l <= (n >> 1); l <<= 1) {
      theta = dir * PI / (double)(l);
      r = complex<double>(cos(theta), sin(theta));
      for (int i = 0; i < n; i += (l << 1)) {
         w = 1.0;
         for (int j = 0; j < l; ++j) {
            u = f[i + j], v = f[i + j + l] * w;
            f[i + j] = u + v, f[i + j + l] = u - v;
            w *= r;
         }//for
      }//for
   }//for
   if (dir == -1)
      for (int i = 0; i < n; ++i)
         f[i] /= double(n);
}//fft

int candidates[1000010];

int main() {
   int until;
   int bestSoFar;
   int Sn, Tn;

   VC P, Q, M;
   scanf(" %s %s", S, T);
   Sn = strlen(S);
   Tn = strlen(T);

   for (int i = 1; i < 1050000; i <<= 1)
      pw2.push_back(i);

   for (int i = 0; i < 4; i++) {
      P.clear();
      Q.clear();
      for (int j = 0; j < Sn; j++)
         P.push_back(S[j] == DNA[i]);
      for (int j = 0; j < Tn; j++)
         P.push_back(0);
      for (int j = Tn - 1; j >= 0; j--)
         Q.push_back(T[j] == DNA[i]);
      for (int j = 0; j < Sn; j++)
         Q.push_back(0);

      until = *lower_bound(pw2.begin(), pw2.end(), (int)P.size());
      while ((int)P.size() < until)
         P.push_back(0);
      while ((int)Q.size() < until)
         Q.push_back(0);

      fft(P);
      fft(Q);
      M = P;
      for (int j = 0; j < (int)M.size(); j++)
         M[j] *= Q[j];
      fft(M, -1);

      for (int j = 0; j < Sn; j++)
         candidates[j + Tn - 1] += M[j + Tn - 1].real() + eps;
   }//for
   bestSoFar = -1;
   for (int i = Tn - 1; i < Sn; i++)
      bestSoFar = max(bestSoFar, candidates[i]);
   printf("%d\n", Tn - bestSoFar);
   return 0;
}//main
