#include <iostream>
#include <vector>
#include <string>
#include <vector>

class Guest {
public:
    Guest() = default;

    Guest(const std::string &name) {
        this->name_ = name;
        is_invited_ = false;
        relatives_ = {};
    }

    std::string getName() const {
        return name_;
    }

    void addRelative(Guest *relative) {
        int left = 0;
        int right = relatives_.size();
        while (left < right) {
            int middle = (left + right) / 2;
            if (relatives_[middle]->name_ < relative->name_) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        relatives_.insert(relatives_.begin() + left, relative);
    }

    void inviteAllRelatives() {
        if (is_invited_) {
            return;
        }
        is_invited_ = true;
        std::cout << name_ << '\n';
        for (auto relative : relatives_) {
            relative->inviteAllRelatives();
        }
    }

private:
    std::string name_;
    std::vector<Guest *> relatives_;
    bool is_invited_;
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    std::vector<Guest> guests(n);
    for (int i = 0; i < n; ++i) {
        int index;
        std::string name;
        std::cin >> index;
        std::cin.ignore();
        std::getline(std::cin, name);
        guests[index] = Guest(name);
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        guests[a].addRelative(&guests[b]);
        guests[b].addRelative(&guests[a]);
    }

    int start;
    std::cin >> start;

    guests[start].inviteAllRelatives();

    return 0;
}
