#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
    vector<int> depth(adj.size(), INT_MAX);

    // Assume vertext 0 is start
    depth[0] = 0;
    queue<int> Q;
    Q.push(0);

    while(!Q.empty()) {
        auto v = Q.front();
        for (auto u:adj[v]) {
            if (depth[u] == INT_MAX) {
                depth[u] = depth[v] + 1;
                Q.push(u);
            } else {
                if (depth[u] % 2 == depth[v] % 2) {
                    return 0;
                }
            }
        }
        Q.pop();
    }
    return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
