#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class UnionFind {
public:
    vector<int> root;
    vector<int> rank;

    UnionFind(int size) : root(size), rank(size, 1) {
        for (int i = 0; i < size; ++i) {
            root[i] = i;
        }
    }

    int find(int x) {
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    void unionNodes(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }
};

vector<vector<int>> kruskal(int n, map<int, vector<pair<int,int>>>& graph) {
    // Collect all edges
    vector<vector<int>> edges;
    for (auto item = graph.begin(); item != graph.end(); item++) {
        int a = item->first;
        vector<pair<int,int>>& neighbors = item->second;
        for (auto& neighbor:neighbors){
            int b = neighbor.first;
            int weight = neighbor.second;
            edges.push_back({weight, a, b});
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    vector<vector<int>> mst;
    UnionFind uf(n);

    // Iterate through sorted edges
    for (auto item = edges.begin(); item != edges.end(); item++){
        int weight = (*item)[0];
        int a = (*item)[1];
        int b = (*item)[2];
        // If the nodes are not already connected
        if (uf.find(a) != uf.find(b)){
            // Connect them
            uf.unionNodes(a, b);
            mst.push_back({a, b, weight});
        }
    }

    return mst;
}

int main() {
    map<int, vector<pair<int, int>>> graph1;
    graph1[0] = {{1, 4}, {7, 8}};
    graph1[1] = {{2, 8}, {7, 11}};
    graph1[2] = {{5, 4}, {3, 7}};
    graph1[3] = {{4, 9}, {5, 14}};
    graph1[4] = {};
    graph1[5] = {{4, 10}};
    graph1[6] = {{5, 2}};
    graph1[7] = {{6, 1}, {8, 7}};
    graph1[8] = {{2, 2}, {6, 6}};
    auto mst = kruskal(9, graph1);

    cout << "Minimum spanning tree edges:" << endl;
    for (auto mst_edge:mst){
        cout << mst_edge[0] << " " << mst_edge[1] << " " << mst_edge[2] << endl;
    }

    return 0;
}

// Expected: 
// 7 6 1
// 6 5 2
// 8 2 2
// 0 1 4
// 2 5 4
// 2 3 7
// 0 7 8
// 3 4 9