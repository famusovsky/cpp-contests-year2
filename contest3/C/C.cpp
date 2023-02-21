#include <iostream>
#include <stack>

bool check(char left, char right) {
    switch (left) {
        case '(':
            return right == ')';
        case '[':
            return right == ']';
        case '{':
            return right == '}';
        default:
            return false;
    }
}

int main() {
    std::stack<char> stack;
    char input;
    while (std::cin >> input) {
        if (input == '(' || input == '[' || input == '{') {
            stack.push(input);
        } else if (!stack.empty() && check(stack.top(), input)) {
            stack.pop();
        } else {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << (stack.empty() ? "YES" : "NO");
    return 0;
}