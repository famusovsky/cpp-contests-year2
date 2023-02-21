#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Heap {
public:
    Heap() = default;

    template <class Iterator>
    Heap(Iterator begin, Iterator end) {
        for (auto it = begin; it != end; ++it) {
            heap_.push_back(*it);
        }
        for (int i = heap_.size() / 2; i >= 0; --i) {
            heapify(i);
        }
    }

    Heap(std::initializer_list<T> list) {
        for (auto &item : list) {
            heap_.push_back(item);
        }
        for (int i = heap_.size() / 2; i >= 0; --i) {
            heapify(i);
        }
    }

    Heap(const Heap &other) {
        heap_ = other.heap_;
    }

    Heap &operator=(const Heap &other) {
        heap_ = other.heap_;
        return *this;
    }

    Heap(Heap &&other) {
        heap_ = std::move(other.heap_);
    }

    Heap &operator=(Heap &&other) {
        heap_ = std::move(other.heap_);
        return *this;
    }

    ~Heap() = default;

    size_t size() const {
        return heap_.size();
    }

    bool empty() const {
        return heap_.empty();
    }

    int top() {
        return heap_[0];
    }

    T extract() {
        T result = heap_[0];
        heap_[0] = heap_[heap_.size() - 1];
        heap_.pop_back();
        heapify(0);
        return result;
    }

    void insert(const T &value) {
        heap_.push_back(value);
        int i = heap_.size() - 1;
        int parent = (i - 1) / 2;
        while (i > 0 && heap_[parent] < heap_[i]) {
            std::swap(heap_[parent], heap_[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void heapify(int i) {
        int left_child, right_child, largest;
        while (true) {
            left_child = 2 * i + 1;
            right_child = 2 * i + 2;
            largest = i;
            if (left_child < static_cast<int>(heap_.size()) && heap_[largest] < heap_[left_child]) {
                largest = left_child;
            }
            if (right_child < static_cast<int>(heap_.size()) &&
                heap_[largest] < heap_[right_child]) {
                largest = right_child;
            }
            if (largest == i) {
                break;
            }
            std::swap(heap_[i], heap_[largest]);
            i = largest;
        }
    }

    std::string toString() {
        std::string result;
        for (int i = 0; i < static_cast<int>(heap_.size()); i++) {
            result += std::to_string(heap_[i]) + " ";
        }
        return result;
    }

private:
    std::vector<T> heap_;
};