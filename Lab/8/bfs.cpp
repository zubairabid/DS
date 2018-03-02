/*
  Find distance between node 0 and node u
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 112345;
vector<int> adj[maxN];
bool visited[maxN];
int level[maxN];
queue<int> track;

/*
  push 0
  go through q:
    mark element in q as visited, add all children in adjacency list of element to q
  pop q
  if q is not empty
    go through q:
      mark element in q as visited, add all children in adjacency list of element to q
*/

// distance from 0 to node destination
int bfs(int destination) {
  // printf("Entered BFS\n");
  int element, child;
  track.push(0);
  visited[0] = true;
  level[0] = 0;

  int clevel = 0;

  while(!track.empty()) {
    // printf("Queue is not empty\n");
    element = track.front();
    // printf("Examining node %d\n", element);
    if(level[element] == clevel) { // if level up, level up
      clevel++;
    }
    visited[element] = true; // mark element in queue as visited

    for(int j = 0; j < adj[element].size(); j++) { //child : adj[element]) { // go through children of element, marking levels if not already there
      child = adj[element][j];
      // printf("%d is a child of %d\n", child, element);
      if(!visited[child]) {
        track.push(child);
        level[child] = clevel;
      }

      if(destination == child) {
        return level[child];
      }

    }
    // printf("%d\n", track.pop());
    // cout << track.pop() << " "; // pop and print element in queue
    track.pop();

  }
}

int main() {
  cout << "fcuk\n";
  for(int i = 0; i < maxN; i++) {
    visited[i] = false;
  }
  // scanf("\n");
  int n, node, child;
  scanf("%d", &n);
  printf("N input done\n");
  for(int i = 0; i < n; i++) {
    scanf("%d %d", &node, &child);
    printf("Input done for %d\n", i);
    adj[node].push_back(child);
    printf("Pushed %d onto %d\n", child, node);
    adj[child].push_back(node);
  }
  int temp;
  scanf("%d", &temp);
  for(int i = 0; i < n; i++) {
    printf("%d : ", i);
    for(int j = 0; j < adj[i].size(); j++) {
      printf("%d ", adj[i][j]);
    }
    printf("\n");
  }

  printf("%d\n", bfs(temp));
}
