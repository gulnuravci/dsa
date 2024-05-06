#include <queue>
#include <vector>
#include <map>
#include <limits.h>
#include <iostream>
using namespace std;

// Initialize the distances to all the nodes to be infinite
struct Distance { int value = INT_MAX; };

// Find the shortest distance from a starting node to an ending node.
map<int, Distance> dijkstra(map<int, vector<pair<int, int>>> graph, int start_node){
    // Map to store the distance from starting node to key node
    map<int, Distance> distances;
    // Set the distance to the start node to be zero
    distances[start_node].value = 0;

    // Create priority queue with min heap
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;
    // Initialize min heap with start node and its distance
    min_heap.push(make_pair(0, start_node));

    // While there are nodes to be explored
    while (!min_heap.empty()){
        // Remove the node at the top of the heap 
        // aka the node with the shortest distance
        int current_distance = min_heap.top().first;
        int current_node = min_heap.top().second;

        // If the current distance from start node to the current node 
        // popped is larger than the distance we already have stored, 
        // then continue because we do not want to consider longer distances
        if (current_distance > distances[current_node].value){ continue; };

        // For each of the current node's neighbors and their weights
        for (auto next_item : graph[current_node]){
            int next_node = next_item.first;
            int weight = next_item.second;
            // Calculate the distance from start node to the next node by
            // summing the current distance plus the weight to the next node
            int next_distance = current_distance + weight;
            // If the next distance calculated is less than what we have in store
            if (next_distance < distances[next_node].value){
                // Update the distance to next node
                distances[next_node].value = next_distance;
                // Push the newfound shortest distance to next node to heap
                // so we can update shorten paths affected by this change
                min_heap.push(make_pair(next_distance, next_node));
            }
        }
    }
    return distances;
}

int main(){
    map<int, vector<pair<int,int>>> graph;

    graph[0].push_back(make_pair(1, 4));
    graph[0].push_back(make_pair(7, 8));
    graph[1].push_back(make_pair(2, 8));
    graph[1].push_back(make_pair(7, 11));
    graph[2].push_back(make_pair(3, 7));
    graph[2].push_back(make_pair(8, 2));
    graph[2].push_back(make_pair(5, 4));
    graph[3].push_back(make_pair(4, 9));
    graph[3].push_back(make_pair(5, 14));
    graph[4].push_back(make_pair(5, 10));
    graph[5].push_back(make_pair(6, 2));
    graph[6].push_back(make_pair(7, 1));
    graph[6].push_back(make_pair(8, 6));
    graph[7].push_back(make_pair(8, 7));

    map<int, Distance> distances = dijkstra(graph, 0);
    cout << "Distances: " << endl;
    for (auto item : distances){
        cout << "Distance to node " << item.first << " is " << item.second.value << endl;
    }
}