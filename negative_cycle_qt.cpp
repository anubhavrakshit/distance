#include <iostream>
#include <vector>
#if 1
#include <bits/stdc++.h>
#endif
using std::vector;


int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, int s) {

    // Run Bellman Ford for |V| iterations and check if we can relax any edge on
    // |V|th iteration

    // Bellman Ford Algo:
    // For Graph G and origin vertex S
    // 1. Set all distances <- INFINITE
    // 2. Set all prev <- NILL
    // 3. for (|V| - 1):
    //		3.1. for all edges:
    //				3.1.1 Relax(edge)
    // 4. for (1 more iteration)
    //		4.1 for all edges:
    //				4.1.1 Relax(edge)

    // Set all vertex distance to Infinite
    int num_vtx = adj.size();
    vector<long> dist(num_vtx, LONG_MAX);
    dist[s] = 0;
    bool did_relax = false;
    for (int i = 0; i < num_vtx - 1; i++) {
        // Randomly go through all edges and try to relax the edge
        for (int u = 0; u < num_vtx; u++) {
            for (int j = 0; j < adj[u].size(); j++) {
                // this the edge u -> v
                int v = adj[u][j];
                int c = cost[u][j];
                long d = dist[v];
                //std::cout << u << "->" << v << "cost = " << c << "\n";
                // Can we relax edge u -> v ?
                if (dist[u] == LONG_MAX) {
                    // source vertex dist is unknown
                    continue;
                } else {
                    if (dist[v] > dist[u] + (long)c) {
                        dist[v] = dist[u] + (long)c;
                        //std::cout << "Relax " << v << " to " << dist[v] << "\n";
                    }
                }
            }
        }
    }

    // Randomly go through all edges and try to relax the edge
    for (int u = 0; u < num_vtx; u++) {
        for (int j = 0; j < adj[u].size(); j++) {
            // this the edge u -> v
            int v = adj[u][j];
            int c = cost[u][j];
            long d = dist[v];
            //std::cout << u << "->" << v << "cost = " << c << "\n";
            // Can we relax edge u -> v ?
            if (dist[u] == LONG_MAX) {
                // source vertex dist is unknown
                continue;
            } else {
                if (dist[v] > dist[u] + (long)c) {
                    dist[v] = dist[u] + (long)c;
                    did_relax = true;
                    //std::cout << "Relax " << v << " to " << dist[v] << "\n";
                }
            }
        }
    }
    if (did_relax) {
        return 1;
    }
    return 0;
}


int negative_cycle_all(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    int num_v = adj.size();

    for (int i = 0; i < num_v; i++) {
        bool has_cycle = negative_cycle(adj, cost, i);
        if (has_cycle) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle_all(adj, cost);
}
