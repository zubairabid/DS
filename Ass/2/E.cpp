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
#include <cmath>
//#include <stdlib.h>

typedef long long int lint;

/*
  Tree representation:
  each tree is an object of the Tree class.
  the Tree class stores:
    number of vertices
    an array of adjacency lists as a vector array, lints
     -the adjacency list array effectively acts as the tree. 1st node is 0, it's connected to list[0], etc
*/
struct Node {
  /* data */
  int64_t x;
  int64_t y;
  int64_t r;
  Node(int64_t x, int64_t y, int64_t r) x(x), y(y), r(r) { }
};

template <typename T>
class Graph {
public:
  void add_node(T& node) {
    data.push_back(node);
  }
  void add_edge(int from, int to) {
    //assert to < graph.size()
    if(from >= graph.size())
      graph.resize(graph.size() * 2);
    //assert to < graph.size()
    graph[from].push_back(to);
  }

  auto begin () const {
    return data.begin();
  }
  auto end () const {
    return data.end();
  }

  std::vector<T>::pointer_type* data() const {
    return data.data();
  }

  void dfs(lint, lint);
  void adjify();
private:
  using basic_graph_t = std::vector<std::vector<int>>;

  std::vector<T> data;
  basic_graph_t graph;

  lint rots; // stores the last rotation on search completion. Might collapse to just a lint.
  void dfs_rec(lint, lint, lint*, lint*);
  void gcd(lint, lint)
};

double center_distance(Node a, Node b) {
  return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
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
  lint i;
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
      }
      else {
        // no print
        rots = 2;
        // std::cout << "Destination was invalid" << '\n';
        // find a way to end this properly
      }
    }

  }
  else {
    for(i = 0; i < adj_list[vert].size(); i++) {
      // std::cout << "Going through list of \t\t\t\t" << vert << '\n';
      // std::cout << "[" << i << "] :";
      // for(lint j = 0; j < adj_list[vert].size(); j++) {
      //   std::cout << adj_list[vert][j] << ' ';
      // }
      // std::cout << '\n';
      if(visited[adj_list[vert][i]] == 0) { // if it hasn't been visited
        // std::cout << "in list of " << vert << ", examining " << dest << '\n';
        rotation[adj_list[vert][i]] = rotation[vert] == 1? -1 : 1;
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
  // std::cout << "Searching from " << vert << " to " << dest << '\n';
  dfs_rec(vert, dest, visited, rotation);

  for(i = 0; i < size; i++) {
    for(j = 0; j < adj_list[i].size(); j++) {
      if(i != adj_list[i][j] && rotation[i] == rotation[adj_list[i][j]]) {
        // std::cout << "Rotation of " << i << " = Rotation of " << j << '\n';
        rots = 2;
        i = size; // to break out of last
        break;
      }
    }
  }

  if(rots == 0) {
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
  else {
    std::cout << "The input gear cannot move." << '\n';
    return;
  }
}
bool is_distance_equal(int x1, int y1, int x2, int y2, int r1, int r2) {
  return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) == (r1 + r2) * (r1 + r2);
}
int main() {
  // input number of gears
  int n;
  std::cin >> n;
  // create tree of n gears
  Graph<Node> graph;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y >> r; // details for each gear
    graph.add_node({.x = x, .y = y, .r = r});
  }

  auto
  for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) {
        if(is_distance_equal())
      }
  }

  t.dfs(0, n-1);

  /* code */
  return 0;
}
