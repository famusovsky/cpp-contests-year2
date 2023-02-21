#include <iostream>

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

/*int main() {
        size_t n;
        std::cin >> n;
        Tree tree;
        for (size_t i = 0; i < n; ++i) {
                int value;
                std::cin >> value;
                tree.insert(value);
        }
        std::cout << tree.getHeight() << std::endl;
        return 0;
}*/