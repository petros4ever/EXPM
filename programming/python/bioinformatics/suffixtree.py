class SuffixTreeNode:
    def __init__(self):
        self.children = {}

class SuffixTree:
    def __init__(self, text):
        self.root = SuffixTreeNode()
        self.text = text
        self.build_suffix_tree()

    def build_suffix_tree(self):
        for i in range(len(self.text)):
            current = self.root
            for c in self.text[i:]:
                if c not in current.children:
                    current.children[c] = SuffixTreeNode()
                current = current.children[c]
            current.children['$'] = None  # Τερματικό σύμβολο

    def search(self, pattern):
        current = self.root
        for c in pattern:
            if c not in current.children:
                return False
            current = current.children[c]
        return True
tree = SuffixTree("banana")
print(tree.search("ana"))   # True
print(tree.search("nana"))  # True
print(tree.search("apple")) # False
