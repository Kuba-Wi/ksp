#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::vector<bool> GetBitsVector(uint32_t inputValue) {
    std::vector<bool> result;
    while (inputValue > 0) {
        result.emplace_back(inputValue & 1);
        inputValue >>= 1;
    }
    return result;
}

std::vector<bool> GetBitsVector(std::string inputValue) {
    return GetBitsVector(std::stoul(inputValue, nullptr, 0));
}

void print(const std::vector<bool>& vec) {
    for (auto v : vec) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

void check(const std::vector<bool>& vec, uint32_t inputValue) {
    uint32_t mask = 1;
    for (auto bit : vec) {
        assert(bit == bool(inputValue & mask));
        mask <<= 1;
    }
}

int main() {
    std::vector<bool> res = GetBitsVector(149);
    print(res);
    check(res, 149);
    res = GetBitsVector(0x95);
    print(res);
    check(res, 0x95);
    res = GetBitsVector("0x95");
    print(res);
    check(res, 0x95);
    res = GetBitsVector("149");
    print(res);
    check(res, 149);
}
