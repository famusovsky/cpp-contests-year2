#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Guest {
    std::string name;
    std::vector<Guest *> relatives = {};
    bool is_invited = false;

    Guest(const std::string &name) {
        this->name = name;
    }

    Guest() = default;
};

void inviteAllRelatives(std::map<std::string, std::vector<Guest *> *> &guests) {
    std::vector<Guest *> relatives;
    for (auto guest : guests) {
        std::cout << guest.first << std::endl;
        for (auto relative : *guest.second) {
            if (!relative->is_invited) {
                relatives.push_back(relative);
                relative->is_invited = true;
            }
        }
    }
    guests.clear();
    if (!relatives.empty()) {
        for (auto relative : relatives) {
            guests[relative->name] = &relative->relatives;
        }
        inviteAllRelatives(guests);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Guest> guests(n);
    for (int i = 0; i < n; ++i) {
        int index;
        std::string name;
        std::cin >> index;
        std::cin.ignore();
        std::getline(std::cin, name);
        guests[index].name = name;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        guests[a].relatives.push_back(&guests[b]);
        guests[b].relatives.push_back(&guests[a]);
    }

    int start;
    std::cin >> start;

    std::map<std::string, std::vector<Guest *> *> guests_map = {
        {guests[start].name, &guests[start].relatives}};
    guests[start].is_invited = true;
    inviteAllRelatives(guests_map);

    return 0;
}
