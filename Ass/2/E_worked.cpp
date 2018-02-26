#include <iostream>
#include <vector>
#include <string>

typedef long long int lint;

typedef struct node {
  lint x;
  lint y;
  lint r;
  lint rotation;
  node() {
      x = 0;
      y = 0;
      r = 0;
      rotation = 0;
  }

} Node;

class Tree {
  static const int max_size = 1005;
public:
  Tree(lint size);
  Node tree[max_size];
  void dfs(lint, lint);
  void adjify();
private:
  lint size;
  std::vector<lint> adj_list[max_size];

  lint rots; // stores the last rotation on search completion. Might collapse to just a lint.
  void dfs_rec(lint, lint, lint*, lint*);
  void gcd(lint, lint);
  bool center_distance(Node, Node);
};

Tree::Tree(lint size) {
  this->size = size;
  rots = 0;
}

bool Tree::center_distance(Node a, Node b) {
  return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)) == (a.r + b.r)*(a.r + b.r);
}

void Tree::gcd(lint a, lint b) {
  lint s, l, temp;
  s = a<b?a:b;
  l = a<b?b:a;

  while (s!=0) {
    temp = l%s;
    l = s;
    s = temp;
  }

  temp = l; // temp stores gcd rn

  std::cout << ((rots==1)?"":"-") << (a/temp) << ":" << (b/temp) << '\n';
}


void Tree::dfs_rec(lint vert, lint dest, lint visited[], lint rotation[]) {
  visited[vert] = 1; // visited
  // rotation should be set in the previous one
  lint i, temp;
  if(vert == dest) {
    if(rots == 0) {
      rots = rotation[vert];
    }
    else {
      if(rots == rotation[vert]) {
      }
      else {
        rots = 2;
        return;
      }
    }
  }
  else {
    for(i = 0; i < adj_list[vert].size(); i++) {
      if(visited[adj_list[vert][i]] == 0) { // if it hasn't been visited in the current path
        temp = (rotation[vert] == 1? -1 : 1); // temp is the potential next rotation.

        if(tree[adj_list[vert][i]].rotation != 0) { // if the vertex was ever approached before and it has a rotation set
           if(temp != tree[adj_list[vert][i]].rotation) { // if the vertex has a different rotation from what we're trying to do
            rots = 2;
            return;
          }
        }
        else {
          rotation[adj_list[vert][i]] = temp; // setting the rotation of the next node
          tree[adj_list[vert][i]].rotation = temp;
        }
        dfs_rec(adj_list[vert][i], dest,  visited, rotation);
      }
    }
  }

  visited[vert] = 0; // unmark
}

void Tree::dfs(lint vert, lint dest) { // finds all paths from vert to dest by dfs
  lint visited[1005];
  lint rotation[1005];
  lint i, j;
  for(i = 0; i < size; i++) {
    visited[i] = 0;
    rotation[i] = 0;
  }
  rotation[vert] = 1;
  tree[vert].rotation = 1;
  dfs_rec(vert, dest, visited, rotation);

  if(rots == 2) {
    std::cout << "The input gear cannot move." << '\n';
    return;
  }
  else if(rots == 0) {
    // untouched
    std::cout << "The input gear is not connected to the output gear." << '\n';
    return;
  }
  else if (rots == 1 || rots == -1){
    gcd(tree[vert].r, tree[dest].r);
  }

}

void Tree::adjify() {
  lint i, j;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      if(i!=j) {
        if(center_distance(tree[i], tree[j])) {
          adj_list[i].push_back(j);
        }
      }
    }
  }
}

//
int main() {
  lint i, j, k, n, x, y, r;// n: number of gears,[2,1000]
  // x, y:[-1e5,1e5]; r:[1,1e5]
  // input number of gears
  std::cin >> n;
  // create tree of n gears
  Tree t(n);

  for (i = 0; i < n; i++) {
    /* code */
    std::cin >> x >> y >> r; // details for each gear
    Node v;
    v.x = x;
    v.y = y;
    v.r = r; // please work, like in C_1
    t.tree[i] = v; // constructing the tree
  }

  // adjacency the tree
  t.adjify();

  t.dfs(0, n-1);

  return 0;
}
