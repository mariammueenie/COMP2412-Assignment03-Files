#include <iostream>
#include <vector>
#include <algorithm> // needed for std::max

class AVLTree {
private:

    // Same basic Node structure used in the course AVL example
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int value)
            : data(value), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root = nullptr;


    // Course example treats a null child's height as -1
    int height(Node* n) {
        if (n == nullptr)
            return -1;

        return n->height;
    }


    // Balance factor = left subtree height - right subtree height
    int balanceFactor(Node* n) {
        if (n == nullptr)
            return 0;

        return height(n->left) - height(n->right);
    }


    // Recalculate the height after inserting or rotating
    void updateHeight(Node* n) {
        if (n != nullptr) {
            n->height =
                std::max(height(n->left), height(n->right)) + 1;
        }
    }


    // Same left-rotation idea as the course example
    Node* rotateLeft(Node* n) {
        std::cout << "Rotating Left around: "
                  << n->data << "\n";

        Node* oldRoot = n;
        Node* newRoot = n->right;

        oldRoot->right = newRoot->left;
        newRoot->left = oldRoot;

        updateHeight(oldRoot);
        updateHeight(newRoot);

        return newRoot;
    }


    // Same right-rotation idea as the course example
    Node* rotateRight(Node* n) {
        std::cout << "Rotating Right around: "
                  << n->data << "\n";

        Node* oldRoot = n;
        Node* newRoot = n->left;

        oldRoot->left = newRoot->right;
        newRoot->right = oldRoot;

        updateHeight(oldRoot);
        updateHeight(newRoot);

        return newRoot;
    }


    // Restore AVL balance if a subtree becomes unbalanced
    Node* balance(Node* n) {
        if (n == nullptr)
            return nullptr;

        updateHeight(n);

        int bf = balanceFactor(n);

        // Left-heavy case
        if (bf > 1) {

            // Left-right case
            if (balanceFactor(n->left) < 0) {
                n->left = rotateLeft(n->left);
            }

            return rotateRight(n);
        }

        // Right-heavy case
        if (bf < -1) {

            // Right-left case
            if (balanceFactor(n->right) > 0) {
                n->right = rotateRight(n->right);
            }

            return rotateLeft(n);
        }

        return n;
    }


    // Recursive AVL insertion from the course example
    Node* insert(Node* n, int value) {

        // Found where the new node belongs
        if (n == nullptr)
            return new Node(value);

        // Normal BST insertion
        if (value < n->data) {
            n->left = insert(n->left, value);
        }
        else if (value > n->data) {
            n->right = insert(n->right, value);
        }
        else {
            // Course example ignores duplicate values
            return n;
        }

        // Correct the balance as recursion returns
        return balance(n);
    }


    // Inorder traversal:
    // left -> root -> right
    //
    // Because this is a BST, inorder gives values
    // from smallest to largest.
    void storeInOrder(
        Node* n,
        std::vector<int>& result
    ) {
        if (n == nullptr)
            return;

        storeInOrder(n->left, result);

        result.push_back(n->data);

        storeInOrder(n->right, result);
    }


public:

    // Public insert calls the recursive insert
    void insert(int value) {
        root = insert(root, value);
    }


    // Store the AVL tree's inorder traversal
    // in a vector so it becomes our sorted result
    void getInOrder(std::vector<int>& result) {
        storeInOrder(root, result);
    }
};


// AVLSort:
// 1. Insert every item into an AVL tree.
// 2. Perform inorder traversal.
// 3. Inorder produces the values in ascending order.
std::vector<int> avlSort(
    const std::vector<int>& arr
) {
    AVLTree tree;

    // Insert all array values into the AVL tree
    for (int value : arr) {
        tree.insert(value);
    }

    // Store inorder traversal as the sorted array
    std::vector<int> sorted;
    tree.getInOrder(sorted);

    return sorted;
}


int main() {

    std::vector<int> arr = {
        5, 2, 4, 6, 1, 3
    };

    std::cout << "Before sorting: ";

    for (int value : arr) {
        std::cout << value << " ";
    }

    std::cout << "\n";


    // Perform AVLSort
    std::vector<int> sorted = avlSort(arr);


    std::cout << "After sorting: ";

    for (int value : sorted) {
        std::cout << value << " ";
    }

    std::cout << "\n";

    return 0;
}
