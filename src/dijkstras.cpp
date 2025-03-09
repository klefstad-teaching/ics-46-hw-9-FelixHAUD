#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    distances[source] = 0;
    previous.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while(!pq.empty()) {
        auto [d_u, u] = pq.top(); 
        pq.pop();

        if (d_u > distances[u]) continue;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            int new_dist = distances[u] + weight;

            if (new_dist < distances[v]) {
                distances[v] = new_dist;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path; 

    for (int arrive = destination; arrive != -1; arrive = previous[arrive]) {
        path.push_back(arrive);
    }

    reverse(path.begin(), path.end());

    return path.empty() ? vector<int>{} : path;
}
void print_path(const vector<int>& v, int total) {
    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

