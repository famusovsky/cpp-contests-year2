#include <iterator>
#include <initializer_list>

class Vector {
public:
    struct Iterator {
        using IteratorCategory = std::random_access_iterator_tag;
        using DifferenceType = std::ptrdiff_t;

        explicit Iterator(int* ptr) : m_ptr_(ptr){};

        int& operator*() const {
            return *m_ptr_;
        }
        int* operator->() {
            return m_ptr_;
        }

        Iterator& operator++() {
            m_ptr_++;
            return *this;
        }
        Iterator operator++(int) {
            int* temp = m_ptr_;
            m_ptr_++;
            return Iterator(temp);
        }

        Iterator& operator--() {
            m_ptr_--;
            return *this;
        }
        Iterator operator--(int) {
            int* temp = m_ptr_;
            m_ptr_--;
            return Iterator(temp);
        }

        Iterator operator+(const DifferenceType& movement) {
            return Iterator(m_ptr_ + movement);
        }
        Iterator operator-(const DifferenceType& movement) {
            return Iterator(m_ptr_ - movement);
        }
        int operator-(const Iterator& iterator) {
            return (m_ptr_ - iterator.m_ptr_);
        }

        Iterator& operator+=(const DifferenceType& movement) {
            m_ptr_ += movement;
            return *this;
        }
        Iterator& operator-=(const DifferenceType& movement) {
            m_ptr_ -= movement;
            return *this;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.m_ptr_ == b.m_ptr_;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.m_ptr_ != b.m_ptr_;
        }

    private:
        int* m_ptr_;
    };

    Vector() {
        point_ = new int[capacity_];
    }

    explicit Vector(size_t n_size) {
        size_ = n_size;
        capacity_ = 2 * size_;
        point_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = 0;
        }
    }

    Vector(const int* vals, size_t size) {
        size_ = size;
        capacity_ = 2 * size_;
        point_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = *(vals + i);
        }
    }

    Vector(const Vector& vec) {
        size_ = vec.size_;
        capacity_ = vec.capacity_;
        point_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = *(vec.point_ + i);
        }
    }

    Vector(std::initializer_list<int> vals) {
        size_ = vals.size();
        capacity_ = 2 * size_;
        point_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = *(vals.begin() + i);
        }
    }

    ~Vector() {
        delete[] point_;
    }

    size_t getSize() const {
        return size_;
    }

    size_t getCapacity() const {
        return capacity_;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    void resize(size_t n_size) {  ////////
        if (n_size >= capacity_) {
            capacity_ = 2 * n_size;
            reallocate(capacity_);
        }
        if (n_size > size_) {
            for (size_t i = size_; i < n_size; ++i) {
                *(point_ + i) = 0;
            }
        }
        size_ = n_size;
    }

    void pushBack(int value) {  //////////////
        if (size_ == capacity_) {
            capacity_ *= 2;
            reallocate(capacity_);
        }
        *(point_ + size_++) = value;
    }

    void popBack() {
        if (isEmpty()) {
            throw std::runtime_error("Empty Array!");
        } else {
            --size_;
        }
    }

    void clear() {
        size_ = 0;
    }

    void insert(size_t pos, int value) {  ////////////
        if (pos > size_) {
            throw std::runtime_error("Wrong Position!");
        } else {
            if (size_ == capacity_) {
                capacity_ *= 2;
                reallocate(capacity_);
            }
            for (size_t i = size_; i > pos; --i) {
                *(point_ + i) = *(point_ + i - 1);
            }
            *(point_ + pos) = value;
            ++size_;
        }
    }

    void erase(size_t pos) {
        if (isEmpty()) {
            throw std::runtime_error("Empty Array!");
        } else if (pos >= size_) {
            throw std::runtime_error("Wrong Position!");
        } else {
            for (size_t i = pos; i < size_ - 1; ++i) {
                *(point_ + i) = *(point_ + i + 1);
            }
            --size_;
        }
    }

    int at(size_t pos) {
        if (pos >= size_) {
            throw std::runtime_error("Wrong Position!");
        } else {
            return *(point_ + pos);
        }
    }

    int front() {
        if (isEmpty()) {
            throw std::runtime_error("Empty Array!");
        } else {
            return *(point_);
        }
    }

    int back() {
        if (isEmpty()) {
            throw std::runtime_error("Empty Array!");
        } else {
            return *(point_ + size_ - 1);
        }
    }

    Iterator begin() {
        return isEmpty() ? end() : Iterator(point_);
    }

    Iterator end() {
        return Iterator(point_ + size_);
    }

    int& operator[](size_t pos) const {
        if (pos >= size_) {
            throw std::runtime_error("Wrong Position!");
        } else {
            return *(point_ + pos);
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        point_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = *(other.point_ + i);
        }
        return *this;
    }

private:
    size_t size_ = 0, capacity_ = 10;
    int* point_;

    void reallocate(size_t n_capacity) {  //////////
        int* n_point = new int[n_capacity];
        std::copy(point_, point_ + size_, n_point);
        delete[] point_;
        point_ = n_point;
    }
};

void merge(Vector::Iterator begin, Vector::Iterator middle, Vector::Iterator end) {
    int n_1 = middle - begin + 1, n_2 = end - middle + 1;
    int* left = new int[n_1];
    int* right = new int[n_2];
    for (int i = 0; i < n_1 - 1; ++i) {
        left[i] = *(begin + i);
    }
    for (int i = 0; i < n_2 - 1; ++i) {
        right[i] = *(middle + i);
    }
    left[n_1 - 1] = INT32_MAX;
    right[n_2 - 1] = INT32_MAX;
    int i = 0, j = 0;
    for (; begin != end; ++begin) {
        if (left[i] <= right[j]) {
            *begin = left[i++];
        } else {
            *begin = right[j++];
        }
    }
    delete[] left;
    delete[] right;
}

void mergeSort(Vector::Iterator begin, Vector::Iterator end) {
    if (begin != end - 1 && begin != end) {
        auto middle = begin + (end - begin) / 2;
        mergeSort(begin, middle);
        mergeSort(middle, end);
        merge(begin, middle, end);
    }
}

void insertionSort(Vector::Iterator begin, Vector::Iterator end) {
    if (begin != end) {
        for (auto i = begin + 1; i != end; ++i) {
            int cur = *i;
            auto j = i - 1;
            while (j - begin >= 0 && *j > cur) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = cur;
        }
    }
}

/*#include <iostream>
int main() {
    Vector vector = {1, 2, 3};
    vector.insert(3,4);
    for (int i = 0; i < vector.getSize(); ++i) {
        std::cout << vector.at(i) << ' ';
    }
}*/