#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using std::queue;
using std::vector;

int distance(vector<vector<int>> &adj, int s, int t)
{
  //write your code here
  vector<int> dist(adj.size());

  //set dist to infinite
  for (auto &x : dist)
  {
    x = INT_MAX;
  }
  queue<int> q;
  // push the start vertex
  q.push(s);
  dist[s] = 0;

  while (!q.empty())
  {
    auto u = q.front();
    for(auto v:adj[u]) {
      if (dist[v] == INT_MAX) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    q.pop();
  }

  if (dist[t] == INT_MAX) {
    return -1;
  }

  return dist[t] - dist[s];
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
