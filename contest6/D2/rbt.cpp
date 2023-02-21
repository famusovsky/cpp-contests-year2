#include <initializer_list>
#include <iostream>
#include <string>

enum Color { RED, BLACK };

template <typename ValueType>
struct Node {
    ValueType value;
    Node<ValueType> *left;
    Node<ValueType> *right;
    Node<ValueType> *parent;
    Color color;

    Node() {
        value = ValueType();
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = RED;
    }
    explicit Node(const ValueType &x) {
        value = x;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = RED;
    }
    /*bool operator==(const Node<ValueType> &other) const {
        return value == other.value && left == other.left && right == other.right &&
               parent == other.parent && color == other.color;
    }*/
};

template <typename T>
class RBTree {
public:
    struct Iterator {
        Iterator() {
            node_ = nullptr;
        }
        explicit Iterator(Node<T> *node) {
            node_ = node;
        }
        const T &operator*() const {
            return node_->value;
        }
        const T *operator->() const {
            return &node_->value;
        }
        Iterator &operator++() {
            if (node_->right) {
                node_ = node_->right;
                while (node_->left) {
                    node_ = node_->left;
                }
                return *this;
            } else {
                Node<T> *copy = node_;
                while (copy->parent && copy->parent->right == copy) {
                    copy = copy->parent;
                }
                if (copy->parent) {
                    if (!copy->parent->left && !copy->parent->right) {
                        return *this;
                    }
                    node_ = copy->parent;
                } else {
                    copy = new Node<T>();
                    copy->parent = node_;
                    node_ = copy;
                }
                return *this;
            }
        }
        Iterator operator++(int) {
            Iterator copy = *this;
            ++*this;
            return copy;
        }
        Iterator &operator--() {
            if (node_->left) {
                node_ = node_->left;
                while (node_->right) {
                    node_ = node_->right;
                }
                return *this;
            } else {
                Node<T> *copy = node_;
                while (copy->parent && copy->parent->left == copy) {
                    copy = copy->parent;
                }
                if (copy->parent) {
                    node_ = copy->parent;
                } else {
                    node_ = nullptr;
                }
                return *this;
            }
        }
        Iterator operator--(int) {
            Iterator copy = *this;
            --*this;
            return copy;
        }
        bool operator==(const Iterator &other) const {
            if (!node_ && !other.node_) {
                return true;
            }
            if (!node_ || !other.node_) {
                return false;
            }
            if (node_->value != other.node_->value) {
                return false;
            }
            return true;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }

    private:
        Node<T> *node_;
    };

    RBTree() {
        root = nullptr;
        size_ = 0;
        begin_ = nullptr;
        end_ = new Node<T>();
    }
    RBTree(std::initializer_list<T> list) {
        root = nullptr;
        size_ = 0;
        begin_ = nullptr;
        end_ = new Node<T>();
        for (auto &value : list) {
            insert(value);
        }
    }
    RBTree(const RBTree &other) {
        root = nullptr;
        size_ = 0;
        begin_ = nullptr;
        end_ = new Node<T>();
        root = getACopy(other.root, nullptr);
        repairPrivates(root);
    }

    RBTree<T> &operator=(const RBTree &other) {
        if (this == &other) {
            return *this;
        }
        deleteTree(root);
        root = nullptr;
        size_ = 0;
        begin_ = nullptr;
        if (end_) {
            delete end_;
        }
        end_ = new Node<T>();
        root = getACopy(other.root, nullptr);
        repairPrivates(root);
        return *this;
    }

    ~RBTree() {
        deleteTree(root);
        delete end_;
    }

    void insert(const T &value) {
        ins(value);
    }
    void erase(const T &value) {
        er(value);
    }

    size_t size() const {
        return size_;
    }
    bool empty() const {
        return size_ == 0;
    }

    Iterator lowerBound(const T &value) const {
        Node<T> *node = lowerBoundNode(value);
        return node ? Iterator(node) : end();
    }

    Iterator find(const T &value) const {
        Node<T> *node = findNode(value);
        return node ? Iterator(node) : end();
    }

    Iterator begin() const {
        return Iterator(begin_);
    }
    Iterator end() const {
        return Iterator(end_);
    }
    std::string toString() const {
        return toString(root);
    }

    Node<T> *root;

private:
    int size_;
    Node<T> *begin_;
    Node<T> *end_;

    void deleteTree(Node<T> *node) {
        if (!node) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void rotateLeft(Node<T> *node) {
        Node<T> *right = node->right;
        node->right = right->left;
        if (right->left) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (!node->parent) {
            root = right;
        } else if (node->value < node->parent->value) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    }

    void rotateRight(Node<T> *node) {
        Node<T> *left = node->left;
        node->left = left->right;
        if (left->right) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (!node->parent) {
            root = left;
        } else if (node->parent->value < node->value) {
            node->parent->right = left;
        } else {
            node->parent->left = left;
        }
        left->right = node;
        node->parent = left;
    }

    void balanceInsertion(Node<T> *node) {
        while (node->parent->color == Color::RED) {
            if (node->parent->value < node->parent->parent->value) {
                if (node->parent->parent->right &&
                    node->parent->parent->right->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    node->parent->parent->right->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node->parent->value < node->value) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                if (node->parent->parent->left && node->parent->parent->left->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    node->parent->parent->left->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node->value < node->parent->value) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateLeft(node->parent->parent);
                }
            }
            if (!node->parent) {
                break;
            }
        }
        root->color = Color::BLACK;
    }

    void ins(T value) {
        Node<T> *node = new Node<T>(value);
        Node<T> *parent_node = nullptr;
        Node<T> *current_node = root;
        while (current_node) {
            parent_node = current_node;
            if (node->value < current_node->value) {
                current_node = current_node->left;
            } else if (current_node->value < node->value) {
                current_node = current_node->right;
            } else {
                delete node;
                return;
            }
        }
        if (!begin_ || node->value < begin_->value) {
            begin_ = node;
        }
        if (!end_) {
            end_ = new Node<T>();
        }
        if (!end_->parent || end_->parent->value < node->value) {
            end_->parent = node;
        }
        size_++;
        node->parent = parent_node;
        if (!parent_node) {
            root = node;
        } else if (node->value < parent_node->value) {
            parent_node->left = node;
        } else {
            parent_node->right = node;
        }
        if (!node->parent) {
            node->color = Color::BLACK;
            return;
        }
        if (!node->parent->parent) {
            return;
        }
        balanceInsertion(node);
    }

    void balanceErase(Node<T> *node) {
        while (node != root && node->color == Color::BLACK) {
            if (node == node->parent->left) {
                Node<T> *brother = node->parent->right;
                if (brother->color == Color::RED) {
                    brother->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rotateLeft(node->parent);
                    brother = node->parent->right;
                }
                if ((brother->left && brother->left->color == Color::RED) ||
                    (brother->right && brother->right->color == Color::RED)) {
                    if (!brother->right || brother->right->color == Color::BLACK) {
                        brother->left->color = Color::BLACK;
                        brother->color = Color::RED;
                        rotateRight(brother);
                        brother = node->parent->right;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    brother->right->color = Color::BLACK;
                    rotateLeft(node->parent);
                    node = root;
                } else {
                    brother->color = Color::RED;
                    node = node->parent;
                }
            } else {
                Node<T> *brother = node->parent->left;
                if (brother->color == Color::RED) {
                    brother->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rotateRight(node->parent);
                    brother = node->parent->left;
                }
                if ((brother->left && brother->left->color == Color::RED) ||
                    (brother->right && brother->right->color == Color::RED)) {
                    if (!brother->left || brother->left->color == Color::BLACK) {
                        brother->right->color = Color::BLACK;
                        brother->color = Color::RED;
                        rotateLeft(brother);
                        brother = node->parent->left;
                    }
                    brother->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    brother->left->color = Color::BLACK;
                    rotateRight(node->parent);
                    node = root;
                } else {
                    brother->color = Color::RED;
                    node = node->parent;
                }
            }
        }
        node->color = Color::BLACK;
    }

    void er(T value) {
        Node<T> *node = findNode(value);
        if (!node) {
            return;
        }
        if (size_ != 1) {
            Node<T> *next = node->right;
            while (next && next->left) {
                next = next->left;
            }
            if (!next) {
                next = node;
            } else {
                node->value = next->value;
            }
            if (next->left || next->right) {
                Node<T> *child = next->left ? next->left : next->right;
                if (next == root) {
                    root = child;
                    child->color = Color::BLACK;
                    child->parent = nullptr;
                } else {
                    if (next->parent->left == next) {
                        next->parent->left = child;
                    } else {
                        next->parent->right = child;
                    }
                    child->parent = next->parent;
                    if (next->color == Color::RED || child->color == Color::RED) {
                        child->color = Color::BLACK;
                    } else {
                        balanceErase(child);
                    }
                }
            } else {
                if (next->color == Color::BLACK) {
                    balanceErase(next);
                }
                if (next->parent->left == next) {
                    next->parent->left = nullptr;
                } else {
                    next->parent->right = nullptr;
                }
            }
            if (next == begin_) {
                begin_ = next->parent;
            }
            if (next == end_->parent) {
                end_->parent = next->parent;
            }
            delete next;
        } else {
            root = nullptr;
            begin_ = nullptr;
            end_ = nullptr;
            delete node;
        }
        size_--;
    }

    Node<T> *findNode(T value) const {
        Node<T> *node = root;
        while (node) {
            if (value < node->value) {
                node = node->left;
            } else if (node->value < value) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    Node<T> *lowerBoundNode(T value) const {
        Node<T> *node = root;
        Node<T> *last = nullptr;
        while (node) {
            if (value < node->value) {
                last = node;
                node = node->left;
            } else if (node->value < value) {
                node = node->right;
            } else {
                return node;
            }
        }
        if (last) {
            return last;
        }
        return nullptr;
    }

    Node<T> *getACopy(Node<T> *node, Node<T> *parent) {
        if (!node) {
            return nullptr;
        }
        Node<T> *copy = new Node<T>(node->value);
        copy->color = node->color;
        copy->parent = parent;
        if (node->right) {
            copy->right = getACopy(node->right, copy);
        }
        parent = copy;
        node = node->left;
        while (node) {
            Node<T> *new_node = new Node<T>(node->value);
            new_node->color = node->color;
            parent->left = new_node;
            new_node->parent = parent;
            if (node->right) {
                new_node->right = getACopy(node->right, new_node);
            }
            parent = new_node;
            node = node->left;
        }
        return copy;
    }

    void repairPrivates(Node<T> *node) {
        if (!node) {
            return;
        }
        if (!begin_ || node->value < begin_->value) {
            begin_ = node;
        }
        if (!end_->parent || end_->parent->value < node->value) {
            end_->parent = node;
        }
        size_++;
        repairPrivates(node->left);
        repairPrivates(node->right);
    }

    std::string toString(Node<T> *node) const {
        if (!node) {
            return "";
        }
        std::string result = std::to_string(node->value) + " " +
                             (node->color == Color::RED ? "R" : "B") + " " +
                             (node->parent ? std::to_string(node->parent->value) : "null") + " " +
                             (node->left ? std::to_string(node->left->value) : "null") + " " +
                             (node->right ? std::to_string(node->right->value) : "null") + "\n";
        result += toString(node->left);
        result += toString(node->right);
        return result;
    }
};

/*int main() {
     RBTree<int> tree;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }
    std::cout << tree.toString();
    RBTree<int> tree2 = {1, 2, 3};
    tree2 = tree;
    RBTree<int> tree3 = tree;
    std::cout << (tree.toString() == tree2.toString() && tree.toString() == tree3.toString())
              << std::endl;
    std::cout << (tree.size() == tree2.size() && tree.size() == tree3.size()) << std::endl;
    std::cout << (*tree.begin() == *tree2.begin() && *tree.begin() == *tree3.begin()) << std::endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    auto it = tree.end();
    while (it != tree.begin()) {
        --it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << *tree.find(27) << *tree.lowerBound(26) << std::endl;
    tree.erase(1);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(17);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(11);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(8);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(13);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(25);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(22);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(15);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(6);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(27);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.insert(1);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.insert(6);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.insert(11);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.insert(8);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(1);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(6);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(11);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(8);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree.erase(13);
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
    tree = {1, 2, 3};
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << tree.size() << std::endl;
}*/
// 10
// 1 6 11 8 13 25 17 22 15 27
//