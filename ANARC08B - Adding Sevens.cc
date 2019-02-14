#include <bits/stdc++.h>
using namespace std;

map<string, int> getDigit;
map<int, string> getCode;

void init() {
   getDigit["063"] = 0;
   getDigit["010"] = 1;
   getDigit["093"] = 2;
   getDigit["079"] = 3;
   getDigit["106"] = 4;
   getDigit["103"] = 5;
   getDigit["119"] = 6;
   getDigit["011"] = 7;
   getDigit["127"] = 8;
   getDigit["107"] = 9;

   getCode[0] = "063";
   getCode[1] = "010";
   getCode[2] = "093";
   getCode[3] = "079";
   getCode[4] = "106";
   getCode[5] = "103";
   getCode[6] = "119";
   getCode[7] = "011";
   getCode[8] = "127";
   getCode[9] = "107";
}//init

int main() {
   ios::sync_with_stdio(false);
   init();
   int n1, n2, i;
   string curr, S, v;
   while (cin >> S && S[0] != 'B') {
      n1 = n2 = i = 0;
      while (true) {
         if (S[i] == '+') {
            i++;
            break;
         }//if
         curr = S[i], curr += S[i + 1], curr += S[i + 2];
         n1 = 10 * n1 + getDigit[curr];
         i += 3;
      }//for
      while (true) {
         if (S[i] == '=')
            break;
         curr = S[i], curr += S[i + 1], curr += S[i + 2];
         n2 = 10 * n2 + getDigit[curr];
         i += 3;
      }//for
      v = to_string(n1 + n2);
      cout << S;
      for (int i = 0; i < (int)v.size(); i++)
         cout << getCode[v[i] - '0'];
      cout << "\n";
   }//while
   return 0;
}//main
