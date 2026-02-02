#include <iostream>
#include "unique_pointer.hpp"
int main(){
    int* x= new int{5};
    ptr::unique_ptr up{x};

    *up=6;
    std::cout << *up << std::endl;

    //std::print("{}\n",*x);

}