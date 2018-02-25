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

/*
3
2 3
1 2 300
2 2 100
2 3
1 1 100
2 2 300
2 3
3 2 150
1 1 200

*/


#include <iostream>
#include <vector>
//#include <stdlib.h>

typedef long long int lint;

typedef struct node {
  /* data */
  lint x;
  lint y;
  lint r;
  std::vector<int> adj_list;

  node() {
      x = 0;
      y = 0;
      r = 0;
  }

} Node;

class Tree {
  Node v = new Node(x);
  std::vector<Node> tree[1005];
public:
  Tree(Node v);

}

Tree::Tree(Node v) {
  this->v = v;
}


//
