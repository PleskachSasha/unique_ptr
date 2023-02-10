#include <iostream>
#include <functional>

template<class T, class Deleter = std::default_delete<T>>
class Unique_ptr {
public:

    Unique_ptr(T* value) : m_value(std::move(value)) {}
    Unique_ptr(T* value, std::function<void(T*)> deleter) : m_value(value), m_deleter(deleter) {}

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

    Unique_ptr(Unique_ptr&& other)noexcept : m_value(other.m_value), m_deleter(other.m_deleter)
    {
        other.m_value = nullptr;
    }
    Unique_ptr& operator=(Unique_ptr&& other) {
        delete m_value;
        m_value = other.m_value;
        m_deleter = other.m_deleter;
        other.m_value = nullptr;
        return *this;
    }

    ~Unique_ptr() {
        m_deleter(m_value);
    }

    T* release() {
        T* tmp = m_value;
        m_value = nullptr;
        return tmp;
    }
    void reset(T* ptr = nullptr) {
        m_value = ptr;
    }
    void swap(Unique_ptr& ptr) {
        T* tmp = ptr.m_value;
        ptr.m_value = m_value;
        m_value = tmp;
    }

    T* get() {
        return *m_value;
    }

    explicit operator bool() {
        if (m_value != nullptr)
            return true;
        else
            return false;
    }

    T& operator *() {
        return *m_value;
    }

    T* operator ->() {
        return *m_value;
    }


private:
    T* m_value;
    std::function<void(T*)> m_deleter = Deleter();
};

template <class T, class Deleter>
class Unique_ptr<T[], Deleter> {
public:
    Unique_ptr(T* value) : m_value(value) {}
    Unique_ptr(T* value, std::function<void(T*)> deleter) : m_value(value), m_deleter(deleter) {}

    Unique_ptr(const Unique_ptr&) = delete;
    Unique_ptr& operator=(const Unique_ptr&) = delete;

    Unique_ptr(Unique_ptr&& other) noexcept : m_value(other.m_value) {    }
    Unique_ptr& operator=(Unique_ptr&& other) {
        delete m_value;
        m_value = other.m_value;
        other.m_value = nullptr;
        return *this;
    }
    ~Unique_ptr() {
        m_deleter(m_value);
    }

    T& operator[](size_t i) {
        return m_value[i];
    }

    T* release() {
        T* tmp = m_value;
        m_value = nullptr;
        return tmp;
    }
    void reset(T* ptr = nullptr) {
        m_value = ptr;
    }
    void swap(Unique_ptr& ptr) {
        T* tmp = ptr.m_value;
        ptr.m_value = m_value;
        m_value = tmp;
    }
    T* get() {
        return *m_value;
    }

    explicit operator bool() {
        if (m_value != nullptr)
            return true;
        else
            return false;
    }

    T& operator *() {
        return *m_value;
    }

    T* operator ->() {
        return *m_value;
    }

private:
    T* m_value;
    std::function<void(T*)> m_deleter = Deleter();

    template<typename T, typename... TS>
    friend Unique_ptr<T> make_unique(TS&&... params);
};

template<typename T, typename... TS>
Unique_ptr<T> make_unique(TS&&... params) {
    return Unique_ptr<T>(new T(std::forward<TS>(params)...));
}

int main()
{
    Unique_ptr<int> c = new int(1);
    //Unique_ptr<int> c1(std::move(c));
    Unique_ptr<int> c3 = std::move(c);
    //std::cout << *c << "  " << *c3;
}