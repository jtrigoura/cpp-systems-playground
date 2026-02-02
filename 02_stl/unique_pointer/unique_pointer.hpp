#pragma once
#include <type_traits>

namespace ptr{
    template <class T>
    class unique_ptr{

        public:
            unique_ptr()noexcept : ptr_(nullptr){}

            unique_ptr(T* ptr)noexcept : ptr_(ptr){}

            unique_ptr(const unique_ptr &other)= delete;

            unique_ptr& operator=(const unique_ptr &other)= delete;

            unique_ptr(unique_ptr &&other)noexcept : ptr_(other.ptr_){
                other.ptr_= nullptr;
            }
            
            unique_ptr&& operator=(unique_ptr &&other)noexcept{
                ptr_=other.ptr_;
                other.ptr= nullptr;
            }

            ~unique_ptr()noexcept(std::is_nothrow_destructible<T>()){
                delete ptr_;
            }

            void reset(T* ptr=nullptr){
                delete ptr_;
                ptr_=ptr;
            }

            T* get()const noexcept{
                return ptr_;
            }

            T* operator->(){
                return ptr_;
            }

            T& operator*(){
                return *ptr_;
            }
        private:
            T* ptr_;

    };
}
