#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int indegree[26], i;
  bool visited[26];
  int freq[26];
  char x;
  bool np = false;
  for(i = 0; i < 26; i++) {
    indegree[i] = 0;
    visited[i] = false;
    freq[i] = 0;
  }
  queue<char> dag;
  vector<string> repeated;
  int n;
  string temp;
  cin >> n;
  for(i = 0; i < n; i++) {
    cin >> temp;
    freq[(int)(temp[0] - 'a')]++;

    repeated.push_back(temp);

    if(freq[(int)(temp[0] - 'a')] == 2 && dag.back() != temp[0]) {
        continue
    }
    else if(!dag.empty() && dag.back() == temp[0]) {
      continue;
    }
    if(i!=0)repeated.pop_back();
    dag.push(temp[0]);
    indegree[(int)(temp[0]-'a')] = (i==0?0:1);
  }
  // TODO: Input and addition to dag
  // TODO:
  //
  if(np)
  {
    cout << "Impossible\n";
    return 0;
  }



  for(i = 0; i < 26; i++) {
    if(indegree[i] == 0 && !visited[i]) {
      x = (char)('a'+i);
      cout << x;
      visited[i] = true;
      if(x == dag.front()) {
        dag.pop();
        if(dag.empty()) {
          continue;
        }
        indegree[(int)(dag.front()-'a')] = 0;
        if(dag.front() < (char)('a' + i + 1)) {
          i = (int)(dag.front() - 'a')-1;
        }
      }
    }
    else if (!visited[i]) {

    }
  }
  cout << "\n";
}
