#include <cstdint>
#include <vector>
#include "MyVector.h"
#include <string>
#include <print>

using namespace std::string_literals;

int main(){
    lib::MyVector<std::vector<int>> vector;
    vector.add(std::vector<int>{});
    vector.add(std::vector<int>{});
    std::print("Size:{}\n", vector.size());
    vector.erase(1);
    std::print("Size:{}\n", vector.size());
    return 0;
}