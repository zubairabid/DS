#include <iostream>
#include <vector>
#include <stdlib.h>

typedef long long int lint;

typedef struct rb {
  lint r;
  lint b;
} RB;

class Tree {

public:
  Tree(lint);
  void contextRun();

private:
  static const lint tmax =  100007;
  static const lint prime_mod = 1000000007;

  lint size;

  // lint b_start, b_level, b_path, b_temp;
  // lint w_start, w_level, w_path, w_temp;
  //
  // lint found;
  // lint flag;

  lint W, R, B;

  std::vector<lint> adj_list[tmax];
  std::vector<lint> weight[tmax];
  lint colour[tmax];
  lint r[tmax];
  lint b[tmax];

  void dfs(lint, lint);
  RB dfs_rec(lint, lint, bool*);
  // old code
  // void dfsc(lint, lint);
  // lint dfsc_rec(lint, lint, bool*);

};

Tree::Tree(lint N) {
  this->size = N;
  this->R = 0;
  this->B = 0;
  this->W = 0;

  // this->b_start = -1;
  // this->b_level = -1;
  // this->b_path = 0;
  // this->b_temp = 0;
  //
  // this->w_start = -1;
  // this->w_level = -1;
  // this->w_path = 0;
  // this->w_temp = 0;
  //
  // this->found = 0;
  // this->flag = 0;
  // old logic mate
}

void Tree::contextRun() {
  lint i, a, b, w;

  // input starts
  for(i = 1; i <= size; i++) {
    std::cin >> colour[i];
    if(colour[i] == 0) {
      R++;
    }
    else {
      B++;
    }
  }

  for(i = 0; i < size-1; i++) {
    std::cin >> a >> b >> w;

    adj_list[a].push_back(b);
    weight[a].push_back(w);

    adj_list[b].push_back(a);
    weight[b].push_back(w);
  }
  // input ends

  dfs(1, 0);
  std::cout << W << '\n';
}

void Tree::dfs(lint vertex, lint prev_weight) { // actual pathing
  // prev_weight is 0 by default
  bool visited[tmax];
  lint i;

  for(i = 0; i <= size; i++) {
    visited[i] = false;
  }
  dfs_rec(vertex, prev_weight, visited);
}

RB Tree::dfs_rec(lint vertex, lint prev_weight, bool visited[]) {
  lint i, t1, t2, t3;
  RB temp;
  visited[vertex] = true;

  if(colour[vertex] == 1) {
    b[vertex] = 1;
    r[vertex] = 0;
  }
  if(colour[vertex] == 0) {
    r[vertex] = 1;
    b[vertex] = 0;
  }

  for(i = 0; i < adj_list[vertex].size(); i++) {
    if(!visited[adj_list[vertex][i]]) {
      temp = dfs_rec(adj_list[vertex][i], weight[vertex][i], visited);
      b[vertex] += temp.b; // now i realsie i coulda done b[adj_list[vertex][i]]
      r[vertex] += temp.r;
    }
  }
  t1 = (B - b[vertex])%prime_mod;
  t1 = (t1 * b[vertex])%prime_mod;
  t2 = (R - r[vertex])%prime_mod;
  t2 = (t2 * r[vertex])%prime_mod;
  t3 = (t1 + t2)%prime_mod;
  t3 = (t3 * prev_weight)%prime_mod;
  W = (W + t3)%prime_mod;
  // W = (W * prev_weight)%prime_mod;
  // W += ((B-b[vertex])*b[vertex]+(R-r[vertex])*r[vertex]) * prev_weight;

  temp.r = r[vertex];
  temp.b = b[vertex];

  visited[vertex] = false;

  return temp;
}

int main() {
  lint N;
  std::cin >> N;
  Tree t(N);
  t.contextRun();
}
