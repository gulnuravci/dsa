class ListNode:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.next = None
        self.prev = None
    
class LRUCache:
    def __init__(self, capacity:int):
        self.capacity = capacity
        self.dict = {}
        self.head = ListNode(-1,-1)
        self.tail = ListNode(-1,-1)
        self.head.next = self.tail
        self.tail.prev = self.head

    def get(self, key:int) -> int:
        """if a node is accessed, it needs to be moved
           to the end of the linked list."""
        if key not in self.dict:
            return -1
        
        node = self.dict[key]
        # remove the node from it's existing place
        # and add it to the end of the linked list
        self.remove(node)
        self.add(node)
        return node.val

    def put(self, key:int, value:int) -> None:
        # if key already exists
        if key in self.dict:
            # get the old node and remove it from the linked list
            old_node = self.dict[key]
            self.remove(old_node)

        # create new node, add the key:node pairing to
        # dictionary, and add node to the end of linked list
        node = ListNode(key, value)
        self.dict[key] = node
        self.add(node)

        # if adding new node exceed capacity
        if len(self.dict) > self.capacity:
            # get the node at the front of the linked list
            node_to_delete = self.head.next
            # delete it from the list
            self.remove(node_to_delete)
            # delete it from the dictionary
            del self.dict[node_to_delete.key]

    def add(self, node):
        # get the node at the end of the linked list
        previous_end = self.tail.prev
        # insert new node after the previous end node
        previous_end.next = node
        # set the prev and next of new end node
        node.prev = previous_end
        node.next = self.tail
        # update the prev of the tail to be the new end node
        self.tail.prev = node
    
    def remove(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev

# Test cases
if __name__ == "__main__":
    # Test case 1
    cache = LRUCache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    assert cache.get(1) == 1  # returns 1
    cache.put(3, 3)  # evicts key 2
    assert cache.get(2) == -1  # returns -1 (not found)
    cache.put(4, 4)  # evicts key 1
    assert cache.get(1) == -1  # returns -1 (not found)
    assert cache.get(3) == 3  # returns 3
    assert cache.get(4) == 4  # returns 4

    # Test case 2
    cache = LRUCache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    assert cache.get(1) == 1  # returns 1
    cache.put(3, 3)  # evicts key 2
    assert cache.get(2) == -1  # returns -1 (not found)
    cache.put(4, 4)  # evicts key 1
    assert cache.get(1) == -1  # returns -1 (not found)
    assert cache.get(3) == 3  # returns 3
    assert cache.get(4) == 4  # returns 4

    print("All test cases passed!")