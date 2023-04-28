#include <iostream>
#include <vector>

void printVectorReverse(const std::vector<char>& vec, size_t n = 0) {
    std::cout << vec[vec.size() - n - 1];
    if (n == vec.size() - 1) {
        std::cout << "\n";
        return;
    }
    std::cout << ",";
    printVectorReverse(vec, n + 1);
}

int main() {
    std::vector<char> input{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    printVectorReverse(input);
}
