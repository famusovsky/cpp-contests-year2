#include <iostream>
#include <algorithm>

class Tree {
public:
    struct Node {
        explicit Node(int value) : data(value), left(nullptr), right(nullptr) {
        }
        int data{};
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Tree() {
        root_ = nullptr;
    }

    ~Tree() {
        deleteTree(root_);
    }

    void insert(int value) {
        root_ = ins(root_, value);
    }

    size_t getHeight() {
        return getHeight(root_);
    }

    bool isBalanced() {
        return isBalanced(root_);
    }

private:
    Node* root_;

    Node* ins(Node* r, int key) {
        if (r == nullptr) {
            return new Node(key);
        } else if (key < r->data) {
            r->left = ins(r->left, key);
        } else if (key > r->data) {
            r->right = ins(r->right, key);
        }
        return r;
    }

    bool isBalanced(Node* r) {
        if (r == nullptr) {
            return true;
        }
        int left_height = r->left == nullptr ? 0 : getHeight(r->left);
        int right_height = r->right == nullptr ? 0 : getHeight(r->right);
        if (abs(left_height - right_height) > 1) {
            return false;
        }
        return isBalanced(r->left) && isBalanced(r->right);
    }

    size_t getHeight(Node* r) {
        size_t left_height = 0;
        size_t right_height = 0;
        if (r->left != nullptr) {
            left_height = getHeight(r->left);
        }
        if (r->right != nullptr) {
            right_height = getHeight(r->right);
        }
        return std::max(left_height, right_height) + 1;
    }

    void deleteTree(Node* r) {
        if (r == nullptr) {
            return;
        }
        deleteTree(r->left);
        deleteTree(r->right);
        delete r;
    }
};

int main() {
    Tree tree;
    int value;
    while (std::cin >> value) {
        if (value == 0) {
            break;
        }
        tree.insert(value);
    }
    std::cout << (tree.isBalanced() ? "YES" : "NO") << std::endl;
    return 0;
}