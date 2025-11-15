#include <iostream>
#include <windows.h>

class BinaryTree
{
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;
        Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr){}
    };
    Node* root = nullptr;
    void inorder(Node* node)
    {
        if(!node) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }
    void destroy(Node* node)
    {
        if(!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void transplant(Node* a, Node* b) //replacing 'a' with node 'b'
    {
        if(a->parent == nullptr) { root = b;}
        else if(a == a->parent->left) { a->parent->left = b;}
        else if(a == a->parent->right) { a->parent->right = b;}
        if(b) { b->parent = a->parent;}
    }
public:
    BinaryTree() = default;
    ~BinaryTree(){ destroy(root);}
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete; 
    BinaryTree& operator=(BinaryTree&&) = delete;
    void insert(int v)
    {
        Node* z = new Node(v);
        Node* y = nullptr;
        Node* x = root;
        while(x)
        {
            y = x;
            if(z->value < x->value) { x = x->left;}
            else { x = x->right;}
        }
        z->parent = y;
        if(y == nullptr){ root = z;}
        else if(z->value < y->value) { y->left = z;}
        else { y->right = z;}
    }
    void delete_node(Node* node) // Removes a node from the tree while maintaining the BST invariant
    {
        if(node->left == nullptr) { transplant(node, node->right);} //for one node
        else if (node->right == nullptr) { transplant(node, node->left);}
        else  //for two nodes;
        {
            Node* succ = min_node(node->right);
            if(succ->parent != node)
            {
                transplant(succ, succ->right);
                succ->right = node->right;
                succ->right->parent = succ;
            }
            transplant(node, succ);
            succ->left = node->left;
            succ->left->parent = succ;
        }
        delete node;
    }
    void print(Node* node)
    {
        inorder(node);
        std::cout << "\n" << std::endl;
    }
    Node* min_node(Node* node)
    {
        while(node && node->left){ node = node->left;}
        return node;
    }
    Node* max_node(Node* node)
    {
        while(node && node->right) { node = node->right;}
        return node;
    }
    Node* successor(Node* node) //Returns the next in order (inorder) node
    {
        if(node->right){ return min_node(node->right);}
        Node* y = node->parent;
        while(y && y->right == node)
        {
            node = y;
            y = y->parent;
        }
        return y;
    }
    Node* predecessor(Node* node) // Returns the previous node in order (inorder)
    {
        if(node->left) { return max_node(node->left);}
        Node* y = node->parent;
        while(y && y->left == node)
        {
            node = y;
            y = y->parent;
        }
        return y;
    }
    Node* get_root() { return root; }
    
    void print_pretty(Node* node, std::string prefix = "", bool isLeft = false) // ASCII tree visualization
    {
        if(!node) return;

        if(node->right)
        {
            print_pretty(node->right, prefix + (isLeft ? "|     " : "    "), false);
        }
        std::cout << prefix;
        std::cout << (isLeft ? "└── " : "┌── ");
        std::cout << node->value << "\n";
        
        if(node->left)
        {
            print_pretty(node->left, prefix + (isLeft ? "    " : "│   "), true);
        }
    }
};

int main()
{
    BinaryTree tree;
    SetConsoleOutputCP(CP_UTF8);
    tree.insert(15);
    tree.insert(10);
    tree.insert(20);
    tree.insert(17);
    tree.insert(8);
    tree.insert(25);
    auto root = tree.get_root();
    tree.print_pretty(tree.get_root());
    return 0;
}
