import heapq
from collections import defaultdict

def dijkstra(graph, start_node, end_node):
    """
    Find the shortest distance from a starting node to an ending 
    node for a weighted directed graph with non-negative weights.
    This is the heap implementation.
    Complexity:
        Time: O(E*log(V))
        Space: O(E+V)
    """
    # initialize the distances to all the nodes to be infinite
    distances = {node:float("inf") for node in graph}
    # set the distances to the start node to be zero
    distances[start_node] = 0
    # initialize min heap with start node and its distance
    priority_queue = [(0, start_node)]

    # while there are nodes to be explored
    while priority_queue:
        # remove the node at the top of the heap
        # aka the node with the shortest distance
        current_distance, current_node = heapq.heappop(priority_queue)

        # if the current distance from start node to the current node 
        # popped is larger than the distance we already have stored, 
        # then continue because we do not want to consider longer distances
        if current_distance > distances[current_node]: continue

        # for each of the current node's neighbors and their weights
        for next_node, weight in graph[current_node]:
            # calculate the distance from start node to the next node by
            # summing the current distance plus the weight to the next node
            next_distance = current_distance + weight
            # if the next distance calculated is less than what we have in store
            if next_distance < distances[next_node]:
                # update the distance to next node
                distances[next_node] = next_distance
                # push the newfound shortest distance to next node to heap
                # so we can update shorten paths affected by this change
                heapq.heappush(priority_queue, (next_distance, next_node))
    
    print("distances:", distances)
    # distances will store the shortest distance from the start node
    return distances[end_node]

if __name__ == "__main__":
    graph = defaultdict(list)
    graph[0].append((1, 4))
    graph[0].append((7, 8))
    graph[1].append((0, 4))
    graph[1].append((2, 8))
    graph[1].append((7, 11))
    graph[2].append((1, 8))
    graph[2].append((3, 7))
    graph[2].append((5, 4))
    graph[2].append((8, 2))
    graph[3].append((2, 7))
    graph[3].append((4, 9))
    graph[3].append((5, 14))
    graph[4].append((3, 9))
    graph[4].append((5, 10))
    graph[5].append((2, 4))
    graph[5].append((3, 14))
    graph[5].append((4, 10))
    graph[5].append((6, 2))
    graph[6].append((5, 2))
    graph[6].append((7, 1))
    graph[6].append((8, 6))
    graph[7].append((0, 8))
    graph[7].append((1, 11))
    graph[7].append((6, 1))
    graph[7].append((8, 7))
    graph[8].append((2, 2))
    graph[8].append((6, 6))
    graph[8].append((7, 7))
    
    # EXPECTED: distances: {0: 0, 1: 4, 2: 12, 3: 19, 4: 21, 5: 11, 6: 9, 7: 8, 8: 14}
    print("distance from 0 to 8: ", dijkstra(graph, 0, 8))