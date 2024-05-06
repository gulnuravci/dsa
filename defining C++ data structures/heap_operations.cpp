#include <queue>
#include <vector>

using namespace std;

priority_queue<int, vector<int>> max_heap;

max_heap.push(1);
max_heap.pop();
top_element = max_heap.top();
queue_size = max_heap.size();
if (max_heap.empty()) { /* Queue is empty */ }
