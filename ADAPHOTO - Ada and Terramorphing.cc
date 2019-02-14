#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000010;

char S[MAXN];
int last = 0, id = 1;
int len[MAXN], lnk[MAXN];
int to[MAXN][4];
int mapping[256];

void buildAutomaton(char* M) {
   int curr, p, c;
   int L = strlen(M);
   for (int i = 0; i < L; i++) {
      c = mapping[(int)M[i]];
      curr = id++;
      len[curr] = len[last] + 1;
      for (p = last; p != -1 && !to[p][c]; p = lnk[p])
         to[p][c] = curr;
      if (p != -1) {
         int q = to[p][c];
         if (len[q] == len[p] + 1)
            lnk[curr] = q;
         else {
            int clone = id++;
            len[clone] = len[p] + 1;
            memcpy(to[clone], to[q], sizeof(to[q]));
            lnk[clone] = lnk[q];
            for (; p != -1 && to[p][c] == q; p = lnk[p])
               to[p][c] = clone;
            lnk[q] = lnk[curr] = clone;
         }//else
      }//if
      last = curr;
   }//for
}//addChar

int traverse(char* M) {
   int l = 0;
   int curr = 0;
   int c;
   int L = strlen(M);
   int ans = 0;
   for (int i = 0; i < L; i++) {
      c = mapping[(int)M[i]];
      while (curr && !to[curr][c]) {
         curr = lnk[curr];
         l = len[curr];
      }//while
      if (to[curr][c]) {
         curr = to[curr][c];
         l++;
      }//if
      ans = max(ans, l);
   }//for
   return ans;
}//traverse

int main() {
   lnk[0] = -1;
   mapping['^'] = 0; mapping['v'] = 1; mapping['-'] = 2; mapping['~'] = 3;
   scanf(" %s", S);
   buildAutomaton(S);
   scanf(" %s", S);
   printf("%d\n", traverse(S));
   return 0;
}//main
