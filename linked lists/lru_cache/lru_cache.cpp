#include <iostream>
#include <unordered_map>

using namespace std;

class ListNode {
public:
    int key;
    int val;
    ListNode* next;
    ListNode* prev;

    ListNode(int k, int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, ListNode*> dict;
    ListNode* head;
    ListNode* tail;

    LRUCache(int cap) : capacity(cap) {
        head = new ListNode(-1, -1);
        tail = new ListNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (dict.find(key) == dict.end()) {
            return -1;
        }

        ListNode* node = dict[key];
        remove(node);
        add(node);
        return node->val;
    }

    void put(int key, int value) {
        if (dict.find(key) != dict.end()) {
            ListNode* old_node = dict[key];
            remove(old_node);
        }

        ListNode* node = new ListNode(key, value);
        dict[key] = node;
        add(node);

        if (dict.size() > capacity) {
            ListNode* node_to_delete = head->next;
            remove(node_to_delete);
            dict.erase(node_to_delete->key);
            // In C++, dynamic memory allocation using new creates objects 
            // on the heap, and delete is used to deallocate this memory 
            // when it is no longer needed. In the LRUCache implementation, 
            // this line ensures that the memory allocated for the node is 
            // released, preventing memory leaks.
            delete node_to_delete;
        }
    }

    void add(ListNode* node) {
        ListNode* previous_end = tail->prev;
        previous_end->next = node;
        node->prev = previous_end;
        node->next = tail;
        tail->prev = node;
    }

    void remove(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};

int main() {
    // Test case 1
    LRUCache cache1(2);
    cache1.put(1, 1);
    cache1.put(2, 2);
    assert(cache1.get(1) == 1);  // returns 1
    cache1.put(3, 3);  // evicts key 2
    assert(cache1.get(2) == -1);  // returns -1 (not found)
    cache1.put(4, 4);  // evicts key 1
    assert(cache1.get(1) == -1);  // returns -1 (not found)
    assert(cache1.get(3) == 3);  // returns 3
    assert(cache1.get(4) == 4);  // returns 4

    // Test case 2
    LRUCache cache2(2);
    cache2.put(1, 1);
    cache2.put(2, 2);
    assert(cache2.get(1) == 1);  // returns 1
    cache2.put(3, 3);  // evicts key 2
    assert(cache2.get(2) == -1);  // returns -1 (not found)
    cache2.put(4, 4);  // evicts key 1
    assert(cache2.get(1) == -1);  // returns -1 (not found)
    assert(cache2.get(3) == 3);  // returns 3
    assert(cache2.get(4) == 4);  // returns 4

    cout << "All test cases passed!" << endl;

    return 0;
}
