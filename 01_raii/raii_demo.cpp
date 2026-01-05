#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

class Buffer {
public:
    // 1) default ctor
    Buffer() : size_(0), data_(nullptr) {}

    // 2) size ctor
    explicit Buffer(std::size_t size)
        : size_(size), data_(size ? new char[size] : nullptr) {
        std::cout << "Allocated " << size_ << " bytes\n";
    }

    // 3) destructor
    ~Buffer() {
        delete[] data_;                 // delete[] nullptr is OK
        std::cout << "Freed buffer\n";
    }

    // 4) copy ctor (deep copy)
    Buffer(const Buffer& other)
        : size_(other.size_),
          data_(other.size_ ? new char[other.size_] : nullptr) {
        if (data_) std::memcpy(data_, other.data_, size_);
        std::cout << "Copied buffer\n";
    }

    // 5) copy assignment (deep copy)
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;

        // Allocate first (strong-ish safety): if allocation throws, *this unchanged
        char* newData = other.size_ ? new char[other.size_] : nullptr;
        if (newData) std::memcpy(newData, other.data_, other.size_);

        delete[] data_;
        data_ = newData;
        size_ = other.size_;

        std::cout << "Copy-assigned buffer\n";
        return *this;
    }

    // 6) move ctor (steal)
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
        std::cout << "Moved buffer\n";
    }

    // 7) move assignment (free current, then steal)
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;

        std::cout << "Move-assigned buffer\n";
        return *this;
    }

    // (optional) helpers for inspection
    std::size_t size() const { return size_; }
    bool empty() const { return data_ == nullptr; }

private:
    std::size_t size_;
    char* data_;
};

int main() {
    Buffer a(1024);

    Buffer b = a;              // copy ctor
    Buffer c = std::move(a);   // move ctor

    Buffer d(256);
    d = b;                     // copy assignment
    d = std::move(c);          // move assignment
}
