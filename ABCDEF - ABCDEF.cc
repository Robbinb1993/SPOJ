#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int S[105];
unordered_map<int, int> V1, V2;
unordered_map<int, int>::iterator it2;

int main() {
   int N;
   int v1, v2;
   LL res = 0;
   scanf("%d", &N);
   for (int i = 0; i < N; i++)
      scanf("%d", &S[i]);
   for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
         for (int k = 0; k < N; k++)
            V1[S[i] * S[j] + S[k]]++;
   for (int i = 0; i < N; i++) {
      if (S[i] == 0)
         continue;
      for (int j = 0; j < N; j++)
         for (int k = 0; k < N; k++)
            V2[(S[j] + S[k]) * S[i]]++;
   }//for
   for (auto it = V1.begin(); it != V1.end(); it++)
      if ((it2 = V2.find(it->first)) != V2.end())
         res += it->second * it2->second;
   printf("%I64d\n", res);
   return 0;
}//main
