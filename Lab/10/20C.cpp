#include <bits/stdc++.h>
#include <iostream>

using namespace std

typedef long long ll;
const ll INF = 1000000007;

vector<pair> adj[10007];

int main() {

  lint no_vert, no_edge, i, a, b, w;

  cin >> no_vert >> no_edge;

  // inserting edges and constructing adjacency list
  for(i = 0; i < no_edge; i++) {
    cin >> a >> b >> w;
    pair <ll, ll> vertex;

    vertex.first = b;
    vertex.second = w;
    adj[a].push_back(vertex);

    vertex.first = a;
    vertex.second = w;
    adj[b].push_back(vertex);
  }

  // constucting the

}

/*
1) Initialize distances of all vertices as infinite.

2) Create an empty set.  Every item of set is a pair
  (weight, vertex). Weight (or distance) is used used
  as first item  of pair as first item is by default
  used to compare two pairs.

3) Insert source vertex into the set and make its
   distance as 0.

4) While Set doesn't become empty, do following
    a) Extract minimum distance vertex from Set.
       Let the extracted vertex be u.
    b) Loop through all adjacent of u and do
       following for every vertex v.

           // If there is a shorter path to v
           // through u.
           If dist[v] > dist[u] + weight(u, v)

               (i) Update distance of v, i.e., do
                     dist[v] = dist[u] + weight(u, v)
               (i) If v is in set, update its distance
                   in set by removing it first, then
                   inserting with new distance
               (ii) If v is not in set, then insert
                    it in set with new distance

5) Print distance array dist[] to print all shortest
   paths.
*/
