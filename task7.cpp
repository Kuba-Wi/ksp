#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class BitStream {
public:
    uint32_t Add(uint32_t bitLength, void* dataAddr) {
        constexpr size_t byteSize = 8;
        uint8_t dataMask;
        uint8_t bit;
        for (size_t bitIndex = 0; bitIndex < bitLength; ++bitIndex) {
            if (_bufferLength % byteSize == 0) {
                _buffer.push_back(0);
            }
            dataMask = 1 << (bitIndex % byteSize);
            bit = (((uint8_t*)dataAddr)[bitIndex / byteSize] & dataMask) != 0;
            _buffer.back() |= (bit << (_bufferLength % byteSize));
            ++_bufferLength;
        }

        return _bufferLength - bitLength;
    }

    uint32_t Get(uint32_t bitLength, void* dataAddr) {
        if (bitLength > _bufferLength) {
            return 0;
        }
        constexpr size_t byteSize = 8;
        std::copy(_buffer.begin(), _buffer.begin() + (bitLength / byteSize), (uint8_t*)dataAddr);
        uint8_t mask = (1 << (bitLength % byteSize)) - 1;
        ((uint8_t*)dataAddr)[bitLength / byteSize] &= (~mask);
        ((uint8_t*)dataAddr)[bitLength / byteSize] |= _buffer[bitLength / byteSize] & mask;
        return bitLength;
    }

    uint32_t GetBitLength() {
        return _bufferLength;
    }

    uint32_t GetData(void* addr, uint32_t maxBitLength) {
        maxBitLength = std::min(maxBitLength, _bufferLength);
        return this->Get(maxBitLength, addr);
    }

    void ResetData() {
        _buffer.clear();
        _bufferLength = 0;
    }
private:
    std::vector<uint8_t> _buffer;
    uint32_t _bufferLength = 0;
};

int main() {
    BitStream stream;
    uint8_t data[2] = {0b11, 0b1100};
    stream.Add(4, data);
    stream.Add(2, data);
    stream.Add(5, data);
    stream.Add(1, data);
    stream.Add(8, data);
    stream.Add(16, data);
    assert(stream.Add(4, data) == 36);
    assert(stream.GetBitLength() == 40);

    uint8_t buf[5] = {0};
    assert(stream.GetData(buf, 100) == 40);
    assert(buf[0] == 243);
    assert(buf[1] == 56);
    assert(buf[2] == 48);
    assert(buf[3] == 192);
    assert(buf[4] == 48);

    buf[0] = 0;
    buf[1] = 0;
    assert(stream.Get(100, buf) == 0);
    assert(stream.Get(12, buf) == 12);
    assert(buf[0] == 243);
    assert(buf[1] == 8);

    stream.ResetData();
    assert(stream.GetBitLength() == 0);

    stream.Add(8, data);
    buf[0] = 0;
    stream.Get(8, buf);
    assert(buf[0] == 0b11);
}
