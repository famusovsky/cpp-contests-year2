#include <iostream>
#include <list>

using std::list;

list<int> merge(const list<int> &first, const list<int> &second) {
    list<int> first_copy = first, second_copy = second, result;
    for (size_t i = 0; i < first.size() + second.size(); ++i) {
        if (first_copy.front() <= second_copy.front()) {
            result.push_back(first_copy.front());
            first_copy.pop_front();
            if (first_copy.empty()) {
                first_copy.push_back(INT32_MAX);
            }
        } else {
            result.push_back(second_copy.front());
            second_copy.pop_front();
            if (second_copy.empty()) {
                second_copy.push_back(INT32_MAX);
            }
        }
    }
    return result;
}