#include <cassert>
#include <string>

uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t bitLength) {
    uint32_t mask = (1 << bitLength) - 1;
    inputValue >>= bitOffset;
    return inputValue & mask;
}

uint32_t GetBitsFromUint32(const char* inputValue, uint8_t bitOffset, uint8_t bitLength) {
    return GetBitsFromUint32(std::stoul(inputValue, nullptr, 0), bitOffset, bitLength);
}

int main() {
    assert(GetBitsFromUint32(0xABCDEF12, 4, 12) == 0xef1);
    assert(GetBitsFromUint32("0xABCDEF12", 4, 12) == 0xef1);
    assert(GetBitsFromUint32("8", 3, 12) == 1);
}
