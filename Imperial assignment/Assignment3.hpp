#include <iostream>
#include <vector>
#include <string>

struct TreeNode;
struct EdgeNode;

typedef std::string tree_t;

struct TreeNode{
    tree_t val;
    EdgeNode* subtree_l;
};

struct EdgeNode{
    tree_t val;
    TreeNode* subtree;
    EdgeNode* next;
};

class A3Tree {

public:
    // Constructor to build the tree from input data
    A3Tree(const std::vector<std::vector<std::string>>& input) {
        t = buildTree(input);
    }

    // Query method to find the result for a given query vector
    std::string query(const std::vector<std::string>& q) {
        TreeNode* currentNode = t;
        int index = 0;
        while (currentNode->subtree_l != nullptr) {
            EdgeNode* currentEdge = currentNode->subtree_l;
            while (currentEdge != nullptr && currentEdge->val != q[index]) {
                currentEdge = currentEdge->next;
            }
            if (currentEdge == nullptr) {
                return "No match found"; // No matching edge
            }
            currentNode = currentEdge->subtree;
            ++index;
        }
        return currentNode->val; // Return the value of the leaf node
    }

    // Method to count all nodes in the tree
    int node_count() {
        return countNodes(t);
    }

    // Method to count all leaf nodes in the tree
    int leaf_node_count() {
        return countLeafNodes(t);
    }

private:
    TreeNode* t; // Root of the tree
    
    // Helper function to build the tree from input data
    TreeNode* buildTree(const std::vector<std::vector<std::string>>& input) {
        if (input.empty()) return nullptr;
    
        TreeNode* root = new TreeNode{input[0][0], nullptr};
        for (size_t i = 1; i < input.size(); ++i) {
            TreeNode* currentNode = root;
            for (size_t j = 1; j < input[i].size(); ++j) {
                EdgeNode* currentEdge = currentNode->subtree_l;
                EdgeNode* prevEdge = nullptr;
    
                while (currentEdge != nullptr && currentEdge->val != input[i][j-1]) {
                    prevEdge = currentEdge;
                    currentEdge = currentEdge->next;
                }
    
                if (currentEdge == nullptr) {
                    currentEdge = new EdgeNode{input[i][j-1], new TreeNode{input[i][j], nullptr}, nullptr};
                    if (prevEdge == nullptr) {
                        currentNode->subtree_l = currentEdge;
                    } else {
                        prevEdge->next = currentEdge;
                    }
                }
    
                currentNode = currentEdge->subtree;
            }
        }
    
        return root;
    }

    // Helper function to count all nodes in the tree
    int countNodes(TreeNode* node) {
        if (node == nullptr) return 0;
        int count = 1; // Count the current node
        EdgeNode* currentEdge = node->subtree_l;
        while (currentEdge != nullptr) {
            count += countNodes(currentEdge->subtree);
            currentEdge = currentEdge->next;
        }
        return count;
    }

    // Helper function to count all leaf nodes in the tree
    int countLeafNodes(TreeNode* node) {
        if (node == nullptr) return 0;
        if (node->subtree_l == nullptr) return 1; // Leaf node
        int count = 0;
        EdgeNode* currentEdge = node->subtree_l;
        while (currentEdge != nullptr) {
            count += countLeafNodes(currentEdge->subtree);
            currentEdge = currentEdge->next;
        }
        return count;
    }
};

int main(){

    // direct initialisation of a vector
    // in this case it's a vector containing vectors
    // each of which contains words (std::string)
    std::vector<std::vector<std::string>> input
    {
        {"temperature", "rain", "wind", "quality"},
        {"high", "yes", "light", "acceptable"},
        {"low", "yes", "light", "acceptable"},
        {"low", "no", "moderate", "good"},
        {"high", "yes", "strong", "poor"},
        {"high", "yes", "moderate", "acceptable"},
        {"high", "no", "moderate", "good"},
        {"low", "yes", "strong", "poor"},
        {"high", "no", "light", "good"},
        {"low", "yes", "moderate", "poor"},
        {"high", "no", "strong", "poor"}
    };

    A3Tree t(input);

    // direct initialisation of a vector:
    std::vector<std::string> q{"low", "yes", "strong"};

    std::cout << t.query(q) << std::endl;
    // this should print: poor

    // assigning new content overwriting the previous content:
    q =  {"high", "yes", "moderate"};

    std::cout << t.query(q) << std::endl;
    // this should print: acceptable

    std::cout << t.node_count() << std::endl;
    // this depends on the actual tree generated,
    // if we consider the tree in the example which
    // has wind in the root node this should print: 10

    std::cout << t.leaf_node_count() << std::endl;
    // this depends on the actual tree generated,
    // if we consider the tree in the example which
    // has wind in the root node this should print: 6

}

