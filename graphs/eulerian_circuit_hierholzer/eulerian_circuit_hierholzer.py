from collections import defaultdict

def hierholzer_algorithm(graph):
    """Find eulerian circuit in directed graph."""
    # represents the number of edges outgoing from a node
    edge_count = {node:len(edges) for node, edges in graph.items()}
    # store final circuit
    circuit = []
    # starting node
    curr_node = list(graph.keys())[0]
    # stack for backtracking and intialize with any node
    curr_path = [curr_node]

    while len(curr_path):
        # if an outgoing edge exists for current node
        if edge_count[curr_node]:
            # visit node and add to stack
            curr_path.append(curr_node)
            
            # find the next node using an edge
            next_node = graph[curr_node][-1]

            # remove the edge that was used
            edge_count[curr_node] -= 1
            graph[curr_node].pop()

            # move to next vertex
            curr_node = next_node
        # if no outgoing edge exists, backtrack to find remaining circuit
        else:
            # add current node with no outgoing edges to circuit
            circuit.append(str(curr_node))

            # backtrack by removing top element from stack
            curr_node = curr_path.pop()

    # print circuit in reverse
    print(" -> ".join(circuit[::-1]))

if __name__ == "__main__":
	graph1 = defaultdict(list)
	graph1[0].append(1)
	graph1[1].append(2)
	graph1[2].append(0)
	hierholzer_algorithm(graph1)
	print()

	graph2 = defaultdict(list)
	graph2[0].extend([1, 6])
	graph2[1].extend([2])
	graph2[2].extend([0,3])
	graph2[3].extend([4])
	graph2[4].extend([2,5])
	graph2[5].extend([0])
	graph2[6].extend([4])
	hierholzer_algorithm(graph2)
	print()
