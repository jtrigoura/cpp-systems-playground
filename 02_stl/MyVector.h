#pragma once

#include <iostream>
#include <stdlib.h>
#include <cstdint>

namespace lib
{
    template <class T>
    class MyVector
    {

    public:
        void add(T&& node)
        {
            if (size_ == capacity_)
                resize_();
            dynamic_array_[size_++] = std::move(node);
        }
        T& get(uint64_t index) const{
            return  dynamic_array_[index];
        }
        void erase(uint64_t index){
            if(index>=size_)
                return;
            for(uint64_t i=index; i+1<size_; ++i)
                dynamic_array_[i]= std::move(dynamic_array_[i+1]);
            --size_;
        }
        uint64_t size() const
        {
            return size_;
        }
        MyVector()
        {
            dynamic_array_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
        MyVector(const MyVector &other)
        {   
            size_ = other.size_;
            capacity_ = other.capacity_;
            dynamic_array_ = new T[other.capacity_];
            for (uint64_t i = 0; i < other.size_; i++)
                dynamic_array_[i] = other.dynamic_array_[i];
        }
        MyVector(MyVector&& other) noexcept{
            size_ = other.size_;
            capacity_ = other.capacity_;
            dynamic_array_= other.dynamic_array_;
            other.size_=0;
            other.capacity_=0;
            other.dynamic_array_= nullptr;
        }
        MyVector& operator=(const MyVector& other){
            if(this==&other)return *this;
            T* new_data= nullptr;
            if(other.capacity_){
                new_data= new T[capacity_];
                for(uint64_t i=0; i<other.size_;++i)
                    new_data[i]= other.dynamic_array_[i];
            }
            delete[]dynamic_array_;
            dynamic_array_=new_data;
            size_= other.size_;
            capacity_= other.capacity_;
            return *this;
        }
        MyVector& operator=(MyVector&& other){
            if(this==&other)return;
            delete[]dynamic_array_;
            dynamic_array_=other.dynamic_array_;
            size_= other.size_;
            capacity_= other.capacity_;

            other.dynamic_array_= nullptr;
            other.size_=0;
            other.capacity_=0;
            
            return *this;
        }
        ~MyVector(){
            delete[] dynamic_array_;
        };

    private:
        T *dynamic_array_;
        uint64_t size_;
        uint64_t capacity_;
        void resize_()
        {
            if(!capacity_)
                ++capacity_;
            capacity_ *= 2;
            T *new_dynamic_array = new T[capacity_];
            for (uint64_t i = 0; i < size_; i++)
            {
                new_dynamic_array[i] = std::move_if_noexcept(dynamic_array_[i]);
            }
            delete[] dynamic_array_;
            dynamic_array_= new_dynamic_array;
            std::cout << "successfully resized \n";
        }
    };
}