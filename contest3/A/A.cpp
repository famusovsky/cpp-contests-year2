#include <iostream>

class Node {
public:
    int data{};
    Node* next;
    Node* previous;
    explicit Node(int data) {
        this->data = data;
        next = nullptr;
        previous = nullptr;
    }
};

class List {
public:
    List() {
        head = nullptr;
        tail = nullptr;
    }
    List(const int* values, size_t size) {
        head = nullptr;
        tail = nullptr;
        for (size_t i = 0; i < size; i++) {
            if (abs(*(values + i)) > 2000000000) {
                throw std::runtime_error("Wrong Value!");
            }
        }
        for (size_t i = 0; i < size; i++) {
            pushBack(*(values + i));
        }
    }
    ~List() {
        while (size_ != 0) {
            // std::cout << head->data << " ";
            pop();
        }
    }

    void pushBack(int value) {
        if (abs(value) > 2000000000) {
            throw std::runtime_error("Wrong Value!");
        } else {
            Node* new_node = new Node(value);
            if (size_ == 0) {
                head = new_node;
                tail = new_node;
                new_node->next = head;
                new_node->previous = head;
            } else {
                new_node->previous = tail;
                new_node->next = head;
                tail->next = new_node;
                head->previous = new_node;
                tail = new_node;
            }
            ++size_;
        }
    }
    void pushFront(int value) {
        if (abs(value) > 2000000000) {
            throw std::runtime_error("Wrong Value!");
        } else {
            Node* new_node = new Node(value);
            if (size_ == 0) {
                head = new_node;
                tail = new_node;
                new_node->next = head;
                new_node->previous = head;
            } else {
                new_node->next = head;
                new_node->previous = tail;
                head->previous = new_node;
                tail->next = new_node;
                head = new_node;
            }
            ++size_;
        }
    }
    int pop() {
        if (size_ == 0) {
            throw std::runtime_error("Can not pop such element!");
        } else {
            int value = head->data;
            if (size_ == 1) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                Node* temp = head->next;
                delete head;
                head = temp;
                head->previous = tail;
                tail->next = head;
            }
            --size_;
            return value;
        }
    }
    int pop(size_t position) {
        if (size_ <= 1 || position >= size_ - 1) {
            throw std::runtime_error("Wrong Position!");
        }
        if (position == size_ - 2) {
            int value = tail->data;
            Node* temp = tail->previous;
            delete tail;
            tail = temp;
            tail->next = head;
            head->previous = tail;
            --size_;
            return value;
        } else if (size_ == 2) {
            int value = tail->data;
            delete tail;
            tail = head;
            head->next = tail;
            head->previous = tail;
            tail->next = head;
            tail->previous = head;
            --size_;
            return value;
        } else {
            Node* temp = head;
            for (size_t i = 0; i < position + 1; i++) {
                temp = temp->next;
            }
            int value = temp->data;
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
            --size_;
            return value;
        }
    }
    void push(int value, size_t position) {
        if (abs(value) > 2000000000) {
            throw std::runtime_error("Wrong Value!");
        } else if (size_ == 0 || position >= size_) {
            throw std::runtime_error("Wrong Position!");
        }
        if (position == size_ - 1) {
            pushBack(value);
            return;
        }
        Node* temp = head;
        Node* new_node = new Node(value);
        for (size_t i = 0; i < position + 1; i++) {
            temp = temp->next;
        }
        temp->previous->next = new_node;
        new_node->previous = temp->previous;
        new_node->next = temp;
        temp->previous = new_node;
        ++size_;
    }

    Node* head{};
    Node* tail{};

private:
    size_t size_ = 0;
};

/*int main() {
    int values[] = {1, 2, 3, 4, 5};
    List list(values, 5);
    list.push(15, 4);
    list.pushBack(6);
    list.pushFront(0);
    list.pop();
    list.pop(2);
    list.push(10, 2);
    return 0;
}*/