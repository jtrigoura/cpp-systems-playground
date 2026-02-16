#include <iostream>
#include "unique_pointer.hpp"
int main(){
    int* x= new int{5};
    {
        ptr::unique_ptr<int> up1(x);
    }
    const ptr::unique_ptr up{new int{6}};


    //std::print("{}\n",*x);

}