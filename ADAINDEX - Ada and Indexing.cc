#include <bits/stdc++.h>
using namespace std;

struct Map {
   int children;
   map<char, Map*> cmap;
   Map() {
      children = 0;
   }
};

int main() {
   int N, M;
   char c;
   Map *temp, *root, *curr;
   root = new Map();
   map<char, Map*>::iterator it;
   scanf("%d %d", &N, &M);
   getchar();
   for (int i = 0; i < N; i++) {
      curr = root;
      c = getchar();
      while (c != '\n') {
         it = curr->cmap.find(c);
         if (it == curr->cmap.end()) {
            temp = new Map();
            curr->cmap.insert(pair<char, Map*>(c, temp));
            curr = temp;
         }//if
         else
            curr = it->second;
         curr->children++;
         c = getchar();
      }//while
   }//for
   for (int i = 0; i < M; i++) {
      curr = root;
      c = getchar();
      while (c != '\n') {
         it = curr->cmap.find(c);
         if (it == curr->cmap.end()) {
            printf("0\n");
            while (c != '\n') {
               c = getchar();
            }
            break;
         }//if
         else
            curr = it->second;
         c = getchar();
      }//while
      if (it != curr->cmap.end())
         printf("%d\n", it->second->children);
   }//for
   return 0;
}//main
