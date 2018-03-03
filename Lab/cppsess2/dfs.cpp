
const int maxN = 10000007;

vector<int> adj[maxN];
bool visited[maxN];

void dfs(int node) {
  visited[node] = true;
  std::cout << node << ' ';

  for(int i = 0; i < adj[node].size(); i++) {
    if(!visited[adj[node][i]])
      dfs(adj[node][i]);
  }
}
