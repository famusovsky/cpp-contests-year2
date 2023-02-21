#include <initializer_list>
#include <string>

enum class Color { RED, BLACK };

template <typename T>
struct FNode {
    T key;
    FNode *left;
    FNode *right;
    FNode *parent;
    Color color;

    FNode<T>(T key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {
    }
};

template <typename T>
class RBTree {
public:
    RBTree() {
        root = nullptr;
        size_ = 0;
    }

    RBTree(std::initializer_list<T> list) {
        root = nullptr;
        size_ = 0;
        for (auto &key : list) {
            ins(key);
        }
    }

    ~RBTree() {
        deleteTree(root);
    }

    void insert(T key) {
        ins(key);
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    T *lowerBound(T key) const {
        auto FNode = lowerBound(root, key);
        return !FNode ? nullptr : &FNode->key;
    }

    T *find(T key) const {
        auto FNode = find(root, key);
        return !FNode ? nullptr : &FNode->key;
    }

    FNode<T> *root;

    std::string toString() const {
        return toString(root);
    }

private:
    int size_;

    void deleteTree(FNode<T> *FNode) {
        if (!FNode) {
            return;
        }
        deleteTree(FNode->left);
        deleteTree(FNode->right);
        delete FNode;
    }

    void rotateLeft(FNode<T> *FNode) {
        FNode<T> *right = FNode->right;
        FNode->right = right->left;
        if (right->left) {
            right->left->parent = FNode;
        }
        right->parent = FNode->parent;
        if (!FNode->parent) {
            root = right;
        } else if (FNode->key < FNode->parent->key) {
            FNode->parent->left = right;
        } else {
            FNode->parent->right = right;
        }
        right->left = FNode;
        FNode->parent = right;
    }

    void rotateRight(FNode<T> *FNode) {
        FNode<T> *left = FNode->left;
        FNode->left = left->right;
        if (left->right) {
            left->right->parent = FNode;
        }
        left->parent = FNode->parent;
        if (!FNode->parent) {
            root = left;
        } else if (FNode->key > FNode->parent->key) {
            FNode->parent->right = left;
        } else {
            FNode->parent->left = left;
        }
        left->right = FNode;
        FNode->parent = left;
    }

    void balance(FNode<T> *FNode) {
        while (FNode->parent->color == Color::RED) {
            if (FNode->parent->key < FNode->parent->parent->key) {
                if (FNode->parent->parent->right &&
                    FNode->parent->parent->right->color == Color::RED) {
                    FNode->parent->color = Color::BLACK;
                    FNode->parent->parent->right->color = Color::BLACK;
                    FNode->parent->parent->color = Color::RED;
                    FNode = FNode->parent->parent;
                } else {
                    if (FNode->key > FNode->parent->key) {
                        FNode = FNode->parent;
                        rotateLeft(FNode);
                    }
                    FNode->parent->color = Color::BLACK;
                    FNode->parent->parent->color = Color::RED;
                    rotateRight(FNode->parent->parent);
                }
            } else {
                if (FNode->parent->parent->left && FNode->parent->parent->left->color == Color::RED) {
                    FNode->parent->color = Color::BLACK;
                    FNode->parent->parent->left->color = Color::BLACK;
                    FNode->parent->parent->color = Color::RED;
                    FNode = FNode->parent->parent;
                } else {
                    if (FNode->key < FNode->parent->key) {
                        FNode = FNode->parent;
                        rotateRight(FNode);
                    }
                    FNode->parent->color = Color::BLACK;
                    FNode->parent->parent->color = Color::RED;
                    rotateLeft(FNode->parent->parent);
                }
            }
            if (!FNode->parent) {
                break;
            }
        }
        root->color = Color::BLACK;
    }

    FNode<T> *lowerBound(FNode<T> *FNode, T key) const {
        if (!FNode) {
            return nullptr;
        } else if (key < FNode->key) {
            FNode<T> *tmp = lowerBound(FNode->left, key);
            return tmp == nullptr ? FNode : tmp;
        } else if (key > FNode->key) {
            return lowerBound(FNode->right, key);
        }
        return FNode;
    }

    void ins(T key) {
        FNode<T> *FNode = new FNode<T>(key);
        FNode<T> *parent_FNode = nullptr;
        FNode<T> *current_FNode = root;
        while (current_FNode) {
            parent_FNode = current_FNode;
            if (FNode->key < current_FNode->key) {
                current_FNode = current_FNode->left;
            } else if (FNode->key > current_FNode->key) {
                current_FNode = current_FNode->right;
            } else {
                delete FNode;
                return;
            }
        }
        size_++;
        FNode->parent = parent_FNode;
        if (!parent_FNode) {
            root = FNode;
        } else if (FNode->key < parent_FNode->key) {
            parent_FNode->left = FNode;
        } else {
            parent_FNode->right = FNode;
        }
        if (!FNode->parent) {
            FNode->color = Color::BLACK;
            return;
        }
        if (!FNode->parent->parent) {
            return;
        }
        balance(FNode);
    }

    FNode<T> *find(FNode<T> *FNode, T key) const {
        if (!FNode) {
            return nullptr;
        }
        if (key < FNode->key) {
            return find(FNode->left, key);
        } else if (key > FNode->key) {
            return find(FNode->right, key);
        } else {
            return FNode;
        }
    }

    std::string toString(FNode<T> *FNode) const {
        if (!FNode) {
            return "";
        }
        std::string result = std::to_string(FNode->key) + " " +
                             (FNode->color == Color::RED ? "R" : "B") + " " +
                             (FNode->parent ? std::to_string(FNode->parent->key) : "null") + " " +
                             (FNode->left ? std::to_string(FNode->left->key) : "null") + " " +
                             (FNode->right ? std::to_string(FNode->right->key) : "null") + "\n";
        result += toString(FNode->left);
        result += toString(FNode->right);
        return result;
    }
};

#include <vector>
#include <iostream>

int main() {
    RBTree<int> tree;
    int n, inp;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> inp;
        tree.insert(inp);
    }
    auto i = tree.find(5);
    if (i) {
        std::cout << *i << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
    i = tree.find(12);
    if (i) {
        std::cout << *i << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
    std::cout << tree.toString() << std::endl;
    return 0;
}