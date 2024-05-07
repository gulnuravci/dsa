from collections import defaultdict

class UnionFind:
    def __init__(self, size):
        self.root = [i for i in range(size)]
        self.rank = [1 for i in range(size)]
    
    def find(self, x):
        if self.root[x] != x:
            self.root[x] = self.find(self.root[x])
        return self.root[x]
    
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.root[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.root[rootX] = rootY
            else:
                self.root[rootY] = rootX
                self.rank[rootX] += 1

def kruskal(n:int, graph:defaultdict(list)):
    # collect all edges
    edges = []
    for a, neighbors in graph.items():
        for b, weight in neighbors:
            edges.append((weight, a, b))
    
    # sort edges by weight
    edges.sort()

    mst = []
    uf = UnionFind(size=n)

    # iterate through sorted edges
    for weight, a, b in edges:
        # if the nodes are not already connected
        if uf.find(a) != uf.find(b):
            # connected them
            uf.union(a, b)
            mst.append((a, b, weight))
    
    return mst

if __name__ == "__main__":
    # Test case 1
    graph1 = defaultdict(list)
    graph1[0] = [(1, 1), (2, 2)]
    graph1[1] = [(0, 1), (2, 3)]
    graph1[2] = [(0, 2), (1, 3)]
    assert kruskal(3, graph1) == [(0, 1, 1), (0, 2, 2)]

    # Test case 2
    graph2 = defaultdict(list)
    graph2[0] = [(1, 4), (2, 3)]
    graph2[1] = [(0, 4), (3, 2)]
    graph2[2] = [(0, 3), (3, 5)]
    graph2[3] = [(1, 2), (2, 5)]
    assert kruskal(4, graph2) == [(1, 3, 2), (0, 2, 3), (0, 1, 4)]
    
    # Test case 3
    graph3 = defaultdict(list)
    graph3[0] = [(1, 4), (7, 8)]
    graph3[1] = [(2, 8), (7, 11)]
    graph3[2] = [(5, 4), (3, 7)]
    graph3[3] = [(4, 9), (5, 14)]
    graph3[4] = []
    graph3[5] = [(4, 10)]
    graph3[6] = [(5, 2)]
    graph3[7] = [(6, 1), (8, 7)]
    graph3[8] = [(2, 2), (6, 6)]
    mst = kruskal(9, graph3)
    assert kruskal(9, graph3) == [(7, 6, 1), (6, 5, 2), (8, 2, 2), (0, 1, 4), (2, 5, 4), (2, 3, 7), (0, 7, 8), (3, 4, 9)]
    
    print("All test cases passed!")