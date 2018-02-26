/*
 * Approach:
 * for each new node construct its adjacency list of other gears it's connected to
 * DFS search from begin to end for paths:
 *  for each path, track the clockwise/counterclockwise
 * if no path exists: print such
 * if there is rotation conflict: print can't move
 * else, print ratio of radii


The graph is an array of structs containing:
1. x
2. y
3. r
4. vector denoting adjacency list.
The index denotes vertex number.

It's bidirectional, so every addition to one adjacency list is mirrored

The adjacency list is constructed while insertion:
  for vertex in graph:
    if center_distance(vertex, current) == vertex.radius+current.radius:
      vertex.adjacency list.push(current)
      current.adjacency list.push(vertex)

// NOTE investigate so as to not repeat

Crucial Bit: the DFS
  maintain a visited list to keep track of visited vertices.
  create a path_rotation array to store the rotation of the last one

  initialise all vertices as not visited

  pathIt(vert_i, vert_f)):
    mark current node (vert_i) as visited
    if current node is vert_f:
      check the path thing
    else:
      for all vertices in adjacent list(vert_i):
        pathIt(new vertex, vert_f)
    remove current node vert_i from visited

 */
#include <iostream>
#include <vector>
#include <string>
// #include <cmath>
//#include <stdlib.h>

typedef long long int lint;

typedef struct node {
  /* data */
  lint x;
  lint y;
  lint r;
  // std::vector<lint> adj_list;
  lint rotation;
  node() {
      x = 0;
      y = 0;
      r = 0;
      rotation = 0;
  }

} Node;

/*
  Tree representation:
  each tree is an object of the Tree class.
  the Tree class stores:
    number of vertices
    an array of adjacency lists as a vector array, lints
     -the adjacency list array effectively acts as the tree. 1st node is 0, it's connected to list[0], etc
*/

class Tree {
  static const int max_size = 1005;
public:
  Tree(lint size);
  Node tree[max_size];
  void dfs(lint, lint);
  void adjify();
private:
  //Node v = new Node();
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
    // do something
    // std::cout << "We reached the destination" << '\n';
    if(rots == 0) {
      // std::cout << "First Destination reached, rots = " << rotation[vert] << '\n';
      rots = rotation[vert];
    }
    else {
      if(rots == rotation[vert]) {
        // good
        // std::cout << "Destination was valid" << '\n';
      } // the else should be accounted for previously
      else {
        // no print
        rots = 2;
        // std::cout << "Destination was invalid" << '\n';
        // find a way to end+ this properly
        return;
      }
    }
    // rots = rotation[vert]; // any exception should be accounted for previously now
  }
  else {
    for(i = 0; i < adj_list[vert].size(); i++) {
      // std::cout << "\t\tGoing through list of " << vert << '\n';
      // std::cout << "[" << i << "] :";
      // for(lint j = 0; j < adj_list[vert].size(); j++) {
      //   std::cout << adj_list[vert][j] << ' ';
      // }
      // std::cout << '\n';
      if(visited[adj_list[vert][i]] == 0) { // if it hasn't been visited in the current path
        // std::cout << "in list of " << vert << ", examining " << dest << '\n';
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
  // rotation[vert] = 0;
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
  // std::cout << "Searching from " << vert << " to " << dest << '\n';
  dfs_rec(vert, dest, visited, rotation);

  // for(i = 0; i < size; i++) {
  //   for(j = 0; j < adj_list[i].size(); j++) {
  //     if(i != adj_list[i][j] && rotation[i] == rotation[adj_list[i][j]]) {
  //       // std::cout << "Rotation of " << i << " = Rotation of " << j << '\n';
  //       rots = 2;
  //       i = size; // to break out of last
  //       break;
  //     }
  //   }
  // }

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
    // print rots==1?'':'-1', gcd(tree[vert], tree[dest])
    // std::cout << "/* message */" << '\n';
    // std::cout << rots << '\n';
    // std::cout << ((rots==1)?"":"-");
    gcd(tree[vert].r, tree[dest].r);
  }

}

void Tree::adjify() {
  lint i, j;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      if(i!=j) {
        if(center_distance(tree[i], tree[j])) {
          // std::cout << "Center distance for " << j << " from " << i << " = " << center_distance(tree[i], tree[j]) << '\n';
          adj_list[i].push_back(j);
        }
      }
    }
    // std::cout << "Created Adjacency list of tree[" << i << "] :";
    // for(lint j = 0; j < adj_list[i].size(); j++) {
    //   std::cout << adj_list[i][j] << ' ';
    // }
    // std::cout << '\n';
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

  /* code */
  return 0;
}
