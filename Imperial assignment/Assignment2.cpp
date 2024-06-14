#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

/// this is just the pre-declaration of both structured data types
/// in order to allow usage in member data fields
struct TreeNode;
struct EdgeNode;

typedef std::string tree_t;

struct EdgeNode{
    TreeNode* subtree;
    EdgeNode* next;
};

struct TreeNode{
    tree_t val;
    EdgeNode* subtree_l;
};

TreeNode* allocate_tree_node(tree_t e){
    TreeNode* tmp = new TreeNode;
    tmp->val = e;
    tmp->subtree_l = NULL;
    return tmp;
}

EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l){
    EdgeNode* tmp = new EdgeNode;
    tmp->subtree = t;
    tmp->next = subtree_l;
    return tmp;
}

void print_tree(TreeNode* t){
    if(t != NULL){
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            print_tree(it->subtree);
            it = it->next;
        }
        std::cout << t->val << std::endl;
    }
}

TreeNode* build_tree_root(tree_t e){
    return allocate_tree_node(e);
}

/// this function looks for the node containing the value e
/// within the tree (whose root is) t
/// and it returns the address of the node if found
/// and NULL otherwise
TreeNode* find_node(tree_t e, TreeNode* t){
    /// TODO: complete this function

    if(t == NULL){
        return NULL;
    }
    else{
        if(t->val == e){
            return t;
        }
        else{
            EdgeNode* it = t->subtree_l;
            while(it != NULL){
                TreeNode* tmp = find_node(e, it->subtree);
                if(tmp != NULL){
                    return tmp;
                }
                it = it->next;
            }
            return NULL;
        }
    }
}

/// this functions adds to the tree (whose root is) t
/// a node with value d as a child of the node with value s
/// (see also how this function is called in the main)
void add_tree_node(tree_t s, tree_t d, TreeNode* t){
    /// TODO: complete this function

    /// within this function you must (meaningfully) use 
    /// function find_node

    TreeNode* node = find_node(s, t);
    if(node != NULL){
        TreeNode* new_node = allocate_tree_node(d);

        EdgeNode* new_edge_node = cons_edge_node(new_node, NULL);

        new_edge_node->next = node->subtree_l;
        node->subtree_l = new_edge_node;
    } 
    else{
        std::cout << "Node with value '" << s << "' not found." << std::endl;
    }
}

/// this function returns the number of nodes in the tree (whose root is) t
/// (see also example of expected output below)
int count_nodes(TreeNode* t){
    /// TODO: complete this function

    if(t == NULL){
        return 0;
    }
    else{
        int count = 1;
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            count += count_nodes(it->subtree);
            it = it->next;
        }
        return count;
    }
}

/// this function returns the number of leaf nodes in the tree (whose root is) t
/// (see also example of expected output below)
int count_leaf_nodes(TreeNode* t){
    /// TODO: complete this function

    if(t == NULL){
        return 0;
    }
    else{
        if(t->subtree_l == NULL){
            return 1;
        }
        else{
            int count = 0;
            EdgeNode* it = t->subtree_l;
            while(it != NULL){
                count += count_leaf_nodes(it->subtree);
                it = it->next;
            }
            return count;
        }
    }
}

/// this function deallocates *all* the memory (dynamically) allocated for the tree
/// this will include instances of the structured data type TreeNode
/// and instances of the structured data type EdgeNode
void deallocate_tree(TreeNode* t){
    /// TODO: complete this function
    if(t != NULL){
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            deallocate_tree(it->subtree);
            EdgeNode* temp = it;
            it = it->next;
            delete temp;
        }
        delete t;
    }
}

int main(){

    std::string filename;
    std::cout << "enter name of input file: " << std::endl;
    std::cin >> filename;

    std::ifstream infile;
    infile.open(filename);

    if(!infile.is_open()){
        std::cout << "error opening file" << std::endl;
        return(EXIT_FAILURE);
    }

    std::string s1, s2;
    infile >> s1;

    TreeNode* t1;
    t1 = build_tree_root(s1);

    while(infile >> s1 >> s2){
        add_tree_node(s1, s2, t1);
    }

    infile.close();

    print_tree(t1);

    std::cout << "node count: " << count_nodes(t1) << std::endl;
    std::cout << "leaf node count: " << count_leaf_nodes(t1) << std::endl;

    deallocate_tree(t1);

}