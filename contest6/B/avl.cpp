#include <iostream>

struct Node {
    int height;
    Node* left;
    Node* right;
    int value;

    Node(int value) : height(1), left(nullptr), right(nullptr), value(value) {
    }
};

class AVLTree {
public:
    AVLTree() {
        root_ = nullptr;
        size_ = 0;
    }

    int getHeight() {
        return getHeight(root_);
    }

    void insert(int value) {
        root_ = insert(root_, value);
    }

    void erase(int value) {
        root_ = erase(root_, value);
    }

    int* find(int value) {
        Node* node = find(root_, value);
        return node == nullptr ? nullptr : &node->value;
    }

    int* traversal() {
        int* result = new int[size_];
        int i = 0;
        traversal(root_, result, i);
        return result;
    }

    int* lowerBound(int value) {
        Node* node = lowerBound(root_, value);
        return node == nullptr ? nullptr : &node->value;
    }

    bool empty() {
        return size_ == 0;
    }

    Node* getRoot() {
        return root_;
    }

    int getSize() {
        return size_;
    }

    ~AVLTree() {
        deleteTree(root_);
    }

private:
    Node* root_;
    int size_;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBFactor(Node* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void fixHeight(Node* node) {
        int height_left = getHeight(node->left);
        int height_right = getHeight(node->right);
        node->height = (height_left > height_right ? height_left : height_right) + 1;
    }

    Node* rotateLeft(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        fixHeight(node);
        fixHeight(right);
        return right;
    }

    Node* rotateRight(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        fixHeight(node);
        fixHeight(left);
        return left;
    }

    Node* balance(Node* node) {
        fixHeight(node);
        if (getBFactor(node) == 2) {
            if (getBFactor(node->right) < 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        if (getBFactor(node) == -2) {
            if (getBFactor(node->left) > 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        return node;
    }

    Node* insert(Node* node, int value) {
        if (!node) {
            size_++;
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return balance(node);
    }

    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

    Node* eraseMin(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = eraseMin(node->left);
        return balance(node);
    }

    Node* erase(Node* node, int value) {
        if (!node) {
            return nullptr;
        }
        if (value < node->value) {
            node->left = erase(node->left, value);
        } else if (value > node->value) {
            node->right = erase(node->right, value);
        } else {
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if (!right) {
                size_--;
                return left;
            }
            Node* min = findMin(right);
            min->right = eraseMin(right);
            min->left = left;
            size_--;
            return balance(min);
        }
        return balance(node);
    }

    Node* find(Node* node, int value) {
        if (!node) {
            return nullptr;
        }
        if (value < node->value) {
            return find(node->left, value);
        } else if (value > node->value) {
            return find(node->right, value);
        } else {
            return node;
        }
    }

    void traversal(Node* node, int* result, int& i) {
        if (!node) {
            return;
        }
        traversal(node->left, result, i);
        result[i++] = node->value;
        traversal(node->right, result, i);
    }

    Node* lowerBound(Node* node, int key) {
        if (!node) {
            return nullptr;
        } else if (key < node->value) {
            Node* tmp = lowerBound(node->left, key);
            return tmp == nullptr ? node : tmp;
        } else if (key > node->value) {
            return lowerBound(node->right, key);
        }
        return node;
    }

    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

/*int main() {
    AVLTree tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }
    int* result = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) {
        std::cout << result[i] << " ";
    }
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        tree.erase(value);
    }
    result = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) {
        std::cout << result[i] << " ";
    }
    delete[] result;
    return 0;
}*/