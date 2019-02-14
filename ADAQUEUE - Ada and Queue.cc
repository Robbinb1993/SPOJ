#include <bits/stdc++.h>
using namespace std;

struct E {
   int v;
   E* prev;
   E* next;
   E() {
     prev = next = NULL;
   }
};

int main() {
   int N;
   int v;
   bool reversed = false;
   char q[10];
   E* root1 = NULL;
   E* root2 = NULL;
   E* e;
   E* temp;
   scanf("%d", &N);
   for (int i = 0; i < N; i++) {
      scanf("%s", q);
      if (strcmp(q, "toFront") == 0) {
         scanf("%d", &v);
         e = new E;
         e->v = v;
         if (root1 == NULL)
            root1 = root2 = e;
         else {
            if (!reversed) {
               temp = root1;
               root1 = e;
               root1->next = temp;
               temp->prev = root1;
            }//if
            else {
               temp = root2;
               root2 = e;
               temp->next = root2;
               root2->prev = temp;
            }//else
         }//else
         e = root1;
      }//if
      else if (strcmp(q, "push_back") == 0) {
         scanf("%d", &v);
         e = new E;
         e->v = v;
         if (root1 == NULL)
            root1 = root2 = e;
         else {
            if (!reversed) {
               temp = root2;
               root2 = e;
               temp->next = root2;
               root2->prev = temp;
            }//if
            else {
               temp = root1;
               root1 = e;
               root1->next = temp;
               temp->prev = root1;
            }//else
         }//else
         e = root1;
      }//else if
      else if (strcmp(q, "front") == 0) {
         if (!reversed) {
            if (!root1)
               printf("No job for Ada?\n");
            else {
               printf("%d\n", root1->v);
               temp = root1;
               root1 = root1->next;
               if (!root1)
                  root2 = NULL;
               else
                  root1->prev = NULL;
               delete temp;
            }//else
         }//if
         else {
            if (!root2)
               printf("No job for Ada?\n");
            else {
               printf("%d\n", root2->v);
               temp = root2;
               root2 = root2->prev;
               if (!root2)
                  root1 = NULL;
               else
                  root2->next = NULL;
               delete temp;
            }//else
         }//else
      }//else if
      else if (strcmp(q, "back") == 0) {
         if (!reversed) {
            if (!root2)
               printf("No job for Ada?\n");
            else {
               printf("%d\n", root2->v);
               temp = root2;
               root2 = root2->prev;
               if (!root2)
                  root1 = NULL;
               else
                  root2->next = NULL;
               delete temp;
            }//else
         }//if
         else {
            if (!root1)
               printf("No job for Ada?\n");
            else {
               printf("%d\n", root1->v);
               temp = root1;
               root1 = root1->next;
               if (!root1)
                  root2 = NULL;
               else
                  root1->prev = NULL;
               delete temp;
            }//else
         }//else
      }//else if
      else if (strcmp(q, "reverse") == 0) {
         reversed = !reversed;
      }//else if
   }//for
   return 0;
}
