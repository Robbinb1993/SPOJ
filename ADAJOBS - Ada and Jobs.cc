#include <bits/stdc++.h>
using namespace std;
typedef pair<string, int> si;
const int INF = 1 << 30;

struct Node {
   int ac;
   int nxt[26];
   int fail;
   Node() {memset(nxt, 0, sizeof(nxt)); ac = INF;}
};

vector<Node> nodes;

char s[1000010];
vector<si> queries;

void addToTrie(const string& S, const int qid) {
   int curr = 0;
   for (int i = 0; i < (int)S.length(); i++) {
      if (!nodes[curr].nxt[S[i] - 'a']) {
         nodes[curr].nxt[S[i] - 'a'] = (int)nodes.size();
         nodes.push_back(Node());
      }//if
      curr = nodes[curr].nxt[S[i] - 'a'];
   }//for
   nodes[curr].ac = min(nodes[curr].ac, qid);
}//addToTrie

void setFailLinks() {
   int tmp, curr;
   queue<int> Q;
   nodes[0].fail = 0;
   Q.push(0);
   while (!Q.empty()) {
      curr = Q.front();
      Q.pop();
      for (int i = 0; i < 26; i++) {
         if (nodes[curr].nxt[i]) {
            Q.push(nodes[curr].nxt[i]);
            tmp = nodes[curr].fail;
            while (tmp && !nodes[tmp].nxt[i])
               tmp = nodes[tmp].fail;
            if (nodes[tmp].nxt[i] && tmp != curr) {
               nodes[nodes[curr].nxt[i]].fail = nodes[tmp].nxt[i];
               nodes[nodes[curr].nxt[i]].ac = min(nodes[nodes[curr].nxt[i]].ac, nodes[nodes[tmp].nxt[i]].ac);
            }//if
            else
               nodes[nodes[curr].nxt[i]].fail = 0;

         }//if
      }//for
   }//while
}//setFailLinks

int main() {
   int N, type, qid, curr;
   bool found;
   scanf("%d", &N);
   qid = 0;
   nodes.push_back(Node());
   for (int i = 0; i < N; i++) {
      scanf("%d %s", &type, s);
      if (type == 0)
         addToTrie(s, qid++);
      else
         queries.push_back(si(s, qid++));
   }//for
   setFailLinks();
   for (int i = 0; i < (int)queries.size(); i++) {
      curr = 0;
      found = false;
      string& S = queries[i].first;
      for (int j = 0; j < (int)S.length(); j++) {
         while (curr && !nodes[curr].nxt[S[j] - 'a'])
            curr = nodes[curr].fail;
         if (nodes[curr].nxt[S[j] - 'a']) {
            curr = nodes[curr].nxt[S[j] - 'a'];
            if (nodes[curr].ac < queries[i].second) {
               found = true;
               break;
            }//if
         }//if
      }//for
      found ? puts("YES") : puts("NO");
   }//for
   return 0;
}//main
