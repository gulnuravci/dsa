class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word: str) -> bool:
        node = self.root
        for char in word:
            if not node.contains_key(char):
                node.put(char, TrieNode())
            node = node.get(char)
        node.is_end = True

    def search(self, word: str) -> bool:
        node = self.root
        for char in word:
            if node.contains_key(char):
                node = node.get(char)
            else:
                return False
        return node != None and node.is_end

    def startsWith(self, prefix: str) -> bool:
        node = self.root
        for char in prefix:
            if node.contains_key(char):
                node = node.get(char)
            else:
                return False
        return True

class TrieNode:
    def __init__(self):
        self.children = [None]*26
        self.is_end = False
    
    def contains_key(self, ch) -> bool:
        return self.children[ord(ch)-ord("a")] != None
    
    def get(self, ch) -> "TrieNode":
        return self.children[ord(ch)-ord("a")]
    
    def put(self, ch, node) -> None:
        self.children[ord(ch)-ord("a")] = node

if __name__ == "__main__":
    trie = Trie()

    # Test case 1: Inserting words and searching for them
    words_to_insert = ["apple", "banana", "car", "cat", "dog", "doggo"]
    for word in words_to_insert:
        trie.insert(word)
    
    # Search for inserted words
    assert trie.search("apple") == True
    assert trie.search("banana") == True
    assert trie.search("car") == True
    assert trie.search("cat") == True
    assert trie.search("dog") == True
    assert trie.search("doggo") == True

    # Test case 2: Searching for words that are not in the Trie
    assert trie.search("applepie") == False
    assert trie.search("bananarama") == False
    assert trie.search("dogs") == False
    assert trie.search("dogg") == False

    # Test case 3: Searching for words that are prefixes of inserted words
    assert trie.startsWith("app") == True
    assert trie.startsWith("ban") == True
    assert trie.startsWith("do") == True

    # Test case 4: Searching for prefixes that are not in the Trie
    assert trie.startsWith("appr") == False
    assert trie.startsWith("bano") == False
    assert trie.startsWith("da") == False

    print("All test cases passed!")