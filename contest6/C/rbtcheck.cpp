#include <cstdint>
#include <iostream>
#include <string>

struct Node {
    int key;
    Node* left;
    Node* right;
    bool is_red;

    Node() {
        this->key = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->is_red = false;
    }

    Node(int key, Node* left, Node* right, char color) {
        this->key = key;
        this->left = left;
        this->right = right;
        this->is_red = (color == 'R') ? true : false;
    }
};

bool checkRBTProperties(Node* root, int& black_count, int current_black_count = 0) {
    if (!root->is_red) {
        ++current_black_count;
    }
    if (root->left == nullptr || root->right == nullptr) {
        ++current_black_count;
        if (black_count == -1) {
            black_count = current_black_count;
        } else if (black_count != current_black_count) {
            return false;
        }
    }
    if (root->left != nullptr) {
        if (root->left->key >= root->key) {
            return false;
        }
        if (root->left->is_red && root->is_red) {
            return false;
        }
        if (!checkRBTProperties(root->left, black_count, current_black_count)) {
            return false;
        }
    }
    if (root->right != nullptr) {
        if (root->right->key <= root->key) {
            return false;
        }
        if (root->right->is_red && root->is_red) {
            return false;
        }
        if (!checkRBTProperties(root->right, black_count, current_black_count)) {
            return false;
        }
    }
    return true;
}

bool isRBT(Node* root) {
    if (root->is_red) {
        return false;
    }
    int black_count = -1;
    return checkRBTProperties(root, black_count, 0);
}

int main() {
    int n, root;
    std::cin >> n;
    if (n == 0) {
        std::cout << "NO" << std::endl;
        return 0;
    } else {
        std::cin >> root;
    }
    Node* nodes = new Node[n + 1];
    for (int i = 0; i < n; ++i) {
        int num, key;
        std::string left, right;
        char color;
        std::cin >> num >> key >> left >> right >> color;
        nodes[num] = Node(key, left == "null" ? nullptr : &nodes[std::stoi(left)],
                          right == "null" ? nullptr : &nodes[std::stoi(right)], color);
    }
    std::cout << (isRBT(&nodes[root]) ? "YES" : "NO") << '\n';
    delete[] nodes;
    return 0;
}