#pragma once
#include <stdexcept>
#include <utility>

namespace ptr {
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename custom_deleter = custom_deleter<T>>
    class unique_ptr
    {
    public:
        unique_ptr(): p_{nullptr} 
        {
        }
        unique_ptr(T* pointer): p_{pointer}
        {
        }

        unique_ptr(const unique_ptr& other){
            throw std::logic_error("Can't copy a unique_ptr");
        }
        unique_ptr& operator=(const unique_ptr& other) {
            throw std::logic_error("Can't copy a unique_ptr");
        }

        unique_ptr(unique_ptr&& other) noexcept 
            : p_{other.release()}
        {
            
        }

        unique_ptr& operator=(unique_ptr&& other) noexcept
        {
            if(other==*this)
                return *this;
            this->reset(other.release());
            return *this;
        }

        ~unique_ptr()
        {   
            deleter(p_);
        }

        T* release()
        {
            return std::exchange(p_, nullptr);
        }

        void reset(T* pointer=nullptr)
        {            
            if(p_!= pointer){
                deleter(p_);
                p_= pointer;
            }
            return;
        }

        bool is_owning() const { 
            return p_!=nullptr;
        }


        T& operator*() const {return *p_;}
        T* operator->() const {return p_;}
        operator bool() const {return p_!=nullptr;}

    private:
        T* p_;
        [[no_unique_address]]custom_deleter deleter{};
    };
}
