#include <iostream>
#include <memory>

template<class T>
class Unique_ptr {
public:
    
    Unique_ptr(T* value): value_(value) {}

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

    Unique_ptr(const Unique_ptr&& other): value_(other){
        other = nullptr;
    }
    Unique_ptr& operator=(const Unique_ptr&& other) {
        delete value_;
        value_ = other;
        other = nullptr;
    }

    T& operator *() {
        return *value_;
    }

    T* operator ->() {
        return value_;
    }

    ~Unique_ptr() {
        delete[] value_;
    }

    T* release() { 
        T* tmp = value_;
        value_ = nullptr;
        return tmp;
    } 
    void reset(/*T ptr = new T()*/) {
        delete value_;
        value_ = nullptr;
        
    }
    T* get() {
        return value_;
    } 
    explicit operator bool() {
        if (value_ != nullptr)
            return true;
        else
            return false;
    } 

    //T& operator[](size_t i); // if Unique_ptr store array

private:
    T* value_;
};


int main()
{
    //Unique_ptr<int> p1(new int(2));
    std::unique_ptr<int> p1(new int(2));
    //std::unique_ptr<int> a (std::make_unique<int>(2));
   
    
    p1.reset();

}