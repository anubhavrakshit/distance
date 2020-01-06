#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    vector<int> dist(adj.size()); // dist of Vertex from s

    for (auto& x:dist) {
        x = INT_MAX;  // set dist to infinite
    }
    dist[s] = 0; // set source Vertex to dist 0

    // Insert all v belonging to V (keyed by dist into a prio q)
    // lets make a pair (dist[v], v) for all v and form a min priority
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>> > PQ;

    // Source vertex will have a dist of 0, lets push it into our PQ and kick of Dijkstra Algo
    PQ.push(std::make_pair(dist[s], s));

    while (!PQ.empty()) {
        pair<int, int> min = PQ.top();
        int d = min.first, v = min.second;
        // skip v if we have already processed
        if (d != dist[v]) {
            PQ.pop();
            continue;
        }
        std::cout << "Min Vertex " << v << " Dist " << d << std::endl;
        // Relax edges of vu and re-insert into PQ
        for (int i = 0; i < adj[v].size(); i++) {
            int u = adj[v][i];
            int c = cost[v][i];

            std::cout << "Cost of " << v << "->" << u << " is " << c << std::endl;
            // Can this happen ??
            if (dist[v] == INT_MAX && dist[u] == INT_MAX) {
                std::cout << "Can not relax edge " << v << "->" << u << std::endl;
            } else {
                if (dist[u] > dist[v] + c) {
                    // can be relaxed
                    dist[u] = dist[v] + c;
                    std::cout << "Relaxed dist " << dist[u] << std::endl;
                    // update the vertex with new key
                    PQ.push(std::make_pair(dist[u],u));
                }
            }

        }
        // Done processing this Vertex
        std::cout << "Processed vertex " << v << "\n\n";
        PQ.pop();
    }

    return dist[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
