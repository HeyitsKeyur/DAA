#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w; // sort by weight
    }
};


class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false; // cycle
        if (rank[xr] < rank[yr]) swap(xr, yr);
        parent[yr] = xr;
        if (rank[xr] == rank[yr]) rank[xr]++;
        return true;
    }
};

// Kruskal’s Algorithm
void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // step 1: sort by weight

    DSU dsu(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) { // if no cycle
            mst.push_back(e);
            totalWeight += e.w;
        }
    }

    cout << "Edges in MST:\n";
    for (auto& e : mst) {
        cout << e.u << " -- " << e.v << " == " << e.w << "\n";
    }
    cout << "Total Weight of MST = " << totalWeight << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    kruskalMST(V, edges);
    return 0;
}
