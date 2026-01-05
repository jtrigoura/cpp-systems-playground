#include <iostream>
#include <cstring>
#include <print>

class Buffer {
public:
    explicit Buffer(size_t size)
        : size_(size), data_(new char[size]) {
        std::cout << "Allocated " << size_ << " bytes\n";
    }

    ~Buffer() {
        delete[] data_;
        std::cout << "Freed buffer\n";
    }

    Buffer(const Buffer& other)
        : size_(other.size_), data_(new char[other.size_]) {
        std::memcpy(data_, other.data_, size_);
        std::cout << "Copied buffer\n";
    }

    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "Moved buffer\n";
    }

private:
    size_t size_;
    char* data_;
};

int main() {
    Buffer a(1024);
    Buffer b = a;
    Buffer c = std::move(a);
    std::print("{}\n",sizeof(Buffer));
}
