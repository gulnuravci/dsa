#include <queue>
#include <vector>

using namespace std;

// Min heaps can be implemented with additional parameter
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;

// Min heap with custom comparator
struct MinComparator {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const{
        return a.first > b.first;
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, MinComparator> min_heap_2;