// Idea: if you have two adjacent equal weighted edges,
//       then only the vertex with both equal weighted
//       edges *might* be happy in the tree containing
//       the subtree comprising the adjacent edges and
//       the vertex
//
// Impl: We can store the edges as a list of weights,
//       corresponding to the list of vertices. So
//       weight[vertex][i] is the weight of the edge from
//       vertex to adj_list[vertex][i].
//
//       adj_list[vertex] is a vector, adj_list is a
//       vector array.

#include <iostream>
#include <vector>
#include <stdlib.h>

typedef long long int lint;

typedef struct node {
  lint a; // Node number a, as per input spec
  lint b; // Node number b, as per input spec
  lint c; // stores weight from a to b
} Node;

class Tree {

public:
  Tree(lint); // declared by passing a size, that is, N
  void commence(); // called from main, because classes are self sufficient


private:
  static const lint tmax_size = 100007;
  static const lint prime_mod = 1000000007;

  lint flag_fucked; // if 1, then answer is 0;
  lint size; // stores the size of the tree: number of nodes
  lint happy; // number of happy nodes. size by default.

  std::vector<lint> adj_list[tmax_size]; // Stores the nodes connected to vertex[i] in adj_list[i]
  std::vector<lint> weights[tmax_size]; // Stores the edge weight from vertex i to vertex adj_list[i][j] inside weights[i][j]

  Node input_array[tmax_size]; // Stores the inputs for easy sorting
  bool possible_happy[tmax_size]; // Stores the possibility that node i is happy

  void dfs(lint, lint, lint);
  void dfs_rec(lint, lint, lint, bool*);
  static int cmpfunc(const void*, const void*);
  lint power(lint, lint, lint);
};

Tree::Tree(lint N) {
  this->size = N;
  this->happy = N;
  this->flag_fucked = 0;

  for(lint i = 0; i < tmax_size; i++) {
    possible_happy[i] = true;
  }

}

lint Tree::power(lint base, lint pow, lint mod) {
  lint res = 1;

	while(pow > 0) {
		if(pow % 2 == 1) {
			pow--;
			res = (res * base) % mod;
		}

		pow /= 2;
		base = (base * base) % mod;
	}
	return res;
}

int Tree::cmpfunc(const void * a, const void * b) { // comparator function
  lint a_weight = ((Node *)a)->c;
  lint b_weight = ((Node *)b)->c;

  return (a_weight - b_weight);
}

void Tree::commence() {
  // :: take N-1 inputs for edges in between the vertices. Stored in input_array
  // :: for easy sorting (sorting makes adjacent equal weight testing easier later)
  lint i, j;

  for(i = 0; i < size - 1; i++) {
    Node n;
    std::cin >> n.a >> n.b >> n.c; // vertex a, vertex b, edge weight
    input_array[i] = n;
  }


  // :: TODO sort input_array by c. qsort should do.
  qsort(input_array, size-1, sizeof(Node), cmpfunc);

  // for(i = 0; i < size; i++) {
    // std::cout << "a : " << input_array[i].a << " b : " << input_array[i].b << " c : " << input_array[i].c << '\n';
  // }

  // :: Add the inputs to the adj_list and the weight_list
  for(i = 0; i < size - 1; i++) {

    // std::cout << "For a : " << input_array[i].a << " b : " << input_array[i].b << " c : " << input_array[i].c << '\n';
    // :: to vertex a, add b to adjacency list, and c to weight
    adj_list[input_array[i].a].push_back(input_array[i].b);
    weights[input_array[i].a].push_back(input_array[i].c);
    // std::cout << "Added " << input_array[i].b << " to adj_list of " << input_array[i].a << "," << input_array[i].c << " to weights." << '\n';
    // :: to vertex b, add a to adjacency list, and c to weight
    adj_list[input_array[i].b].push_back(input_array[i].a);
    weights[input_array[i].b].push_back(input_array[i].c);
    // std::cout << "Added " << input_array[i].a << " to adj_list of " << input_array[i].b << ", " << input_array[i].c << " to weights." << '\n';

  }

  // :: Now, we'll iterate through the adj_list.
  // :: In there, check that no consecutive elements have the same weight
  // :: If they do, action shall be specified.
  for(i = 1; i <= size; i++) { // it's 1-indexed
    //
    // std::cout << i << " : ";
    // for(j = 0; j < adj_list[i].size(); j++) {
    //   std::cout << adj_list[i][j] << " ";
    // }
    // std::cout  << '\n' << i << " : ";
    // for(j = 0; j < adj_list[i].size(); j++) {
    //   std::cout << weights[i][j] << " ";
    // }

    // std::cout << "\n-----\n";

    for(j = 0; j < adj_list[i].size()-1; j++) { // for each vertex connected to i
      // std::cout << "comparing vertices " << i << " and " << adj_list[i][j] << '\n';
      if(weights[i][j] == weights[i][j+1]) { // :: Now, if two edges on vertex i
        // :: have the same weight, then in the subtree containing edge-vertex-edge,
        // :: only vertex i will have happiness. So we DFS on the left and right
        // :: subtrees of i, assign every vertex to unhappy.
        // :: Now, if during DFS any two adjacent edges are equal, answer is 0.
        // :: This specific case shall be dealt with in the dfs function
        // std::cout << "vertex " << i << " is repeat edges with " << adj_list[i][j] << " and " << adj_list[i][j+1] << '\n';
        dfs(i, adj_list[i][j], weights[i][j]); // :: runs the dfs on vertex j, keeping edge weight in mind
        dfs(i, adj_list[i][j+1], weights[i][j+1]); // :: likewise
      }
      if(flag_fucked == 1) {
        // The answer will be 0
        break;
      }
    }
    if(flag_fucked == 1) {
      // The answer will be 0
      break;
    }
  }
  // for(i = 1; i <= size; i++) {
  //   // std::cout << possible_happy[i] << " ";
  // }
  // std::cout << '\n';
  if(flag_fucked == 1) {
    std::cout << "0" << '\n';
  }
  else {
    // TODO print happy^happy^happy
    lint result = power(happy, (power(happy, happy, prime_mod-1)), prime_mod);
    std::cout << result << '\n';
  }

}

void Tree::dfs(lint source, lint vertex, lint weight) { // helper function for the actual dfs
  // std::cout << "Checking node " << vertex << ", weight as " << weight << '\n';
  bool visited[tmax_size]; // stores the path of dfs
  lint i = 0;

  for(i = 0; i < tmax_size; i++) {
    visited[i] = false;
  }
  if(possible_happy[vertex]) dfs_rec(vertex, weight, source, visited); // :: then we run a dfs on this.
}

void Tree::dfs_rec(lint vertex, lint weight, lint parent, bool visited[]) {
  visited[vertex] = true;
  // std::cout << "//vertex " << vertex << " visited status : " << visited[vertex] << '\n';
  lint i;
  // :: now here, make everything unhappy.
  possible_happy[vertex] = false;
  // std::cout << "happy[" <<vertex<<" is false" << '\n';
  happy--;

  if(adj_list[vertex].size() == 1) {
    possible_happy[vertex] = false;
    return;
  }

  // :: now go further in the DFS for vertex
  for(i = 0; i < adj_list[vertex].size(); i++) { // loops through adjacency list of vertex
    // std::cout << "vertex " << adj_list[vertex][i] << " visited status : " << visited[adj_list[vertex][i]] << '\n';
    // std::cout << "In the list of " << vertex << " : " << adj_list[vertex][i] << '\n';

    if(parent == adj_list[vertex][i]) { // compare with parent
      continue;
    }

    if(visited[adj_list[vertex][i]]) {
      continue;
    }

    // :: if any weight is equal now, FUCK THIS SHIT I'MMA ZERO OUT
    if(weights[vertex][i] == weight) { // edge joining adj_list[vertex][i] has same weight
      // std::cout << "for vertex " << vertex << " and " << adj_list[vertex][i] << ", weights are equal: " << weight << '\n';
      flag_fucked = 1;
      return;
    }

    // :: else, we just go ahead with dfs

    if(possible_happy[adj_list[vertex][i]]) dfs_rec(adj_list[vertex][i], weights[vertex][i], vertex, visited);

  }

  visited[vertex] = false;
}

int main() {
  // Take N into input. Declare a Tree with size N
  lint N;
  std::cin >> N;
  if(N == 1) {
    std::cout << "1" << '\n';
  }
  else {
    Tree t(N);
    t.commence();
  }
}
