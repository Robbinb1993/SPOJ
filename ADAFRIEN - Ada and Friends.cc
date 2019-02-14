#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
char name[50];
vector<LL> V;
map<string, LL> expenses;

int main() {
   int Q, K, E;
   LL sum;
   while (scanf("%d %d", &Q, &K) == 2) {
      expenses.clear();
      V.clear();
      while (Q--) {
         scanf(" %s %d", name, &E);
         expenses[name] += E;
      }//while
      for (auto& it : expenses)
         V.push_back(it.second);
      sort(V.begin(), V.end(), greater<LL>());
      sum = 0;
      for (int i = 0; i < K && i < (int)V.size(); i++)
         sum += V[i];
      printf("%lld\n", sum);
   }//while
   return 0;
}//main
