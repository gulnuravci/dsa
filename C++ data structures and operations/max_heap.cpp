#include <queue>
#include <vector>

using namespace std;

// Max heaps are the default in C++
priority_queue<pair<int,int>, vector<pair<int,int>>> max_heap;
priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> max_heap_2;

// Max heap with custom comparator
struct MaxComparator {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) const {
        return a.first < b.first;
    }
};
priority_queue<pair<int,int>, vector<pair<int,int>>, MaxComparator> max_heap_3;