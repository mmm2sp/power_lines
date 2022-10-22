#include <iostream>

template <typename T>
class Vector {

public:
    size_t size = 0; //capacity
    size_t lenght = 0; //сколько элементов занято
    T* buffer = nullptr;

    Vector(): size(10), buffer(new T[10]) {}

    Vector(Vector<T> const& vec): size(vec.size), lenght(vec.length) {
        buffer = new T[size];
        for (size_t i = 0; i < lenght; i++) {
            buffer[i] = vec.buffer[i];
        }
    };

    Vector(Vector<T> && vec) noexcept: size(vec.size), lenght(vec.lenght) {
        buffer = vec.buffer;
        vec.buffer = nullptr;
    };

    void add_memory() {
        auto new_buffer = new T[size * 2];
        for (size_t i = 0; i < lenght; i++) {
            new_buffer[i] = buffer[i];
        }
        size = 2 * size;
        delete[] buffer;
        this->buffer = new_buffer;
    };

    void push_back(const T& value) {
        if (lenght + 1 > size) {
            this->add_memory();
        }
        buffer[lenght] = value;
        lenght = lenght + 1;
    };

    T& top() {
        if (lenght == 0)
            throw std::string("there are no elements in vector");
        return buffer[lenght];
    };

    void pop() {
        if (lenght == 0) {
            throw std::string("there are no elements in vector");
        }
        else {
            lenght = lenght - 1;
        }
    };

    bool is_empty() const {
        if (lenght == 0)
            return true;
        else
            return false;
    };

    size_t capacity() const {
        return size;
    };

    T& at(size_t index) {
        if (index >= 0 && index <= lenght)
            return buffer[index];
        else
            throw std::string("index out of range");
    };

    T& operator[](size_t index) {
        return buffer[index];
    };

    ~Vector() {
        delete[] buffer;
    };
};

int main()
{
    Vector<int> vec = Vector<int>();
    try {
        vec.pop();
    }
    catch(std::string s) {
        std::cout << s << '\n';
    }
    try {
        int a = vec.top();
    }
    catch(std::string s) {
        std::cout << s << '\n';
    }
    vec.push_back(1);
    std::cout << vec.capacity() << '\n';
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    std::cout << vec.capacity() << '\n';
    std::cout << vec[3] << '\n';
    try {
        vec.at(20);
    }
    catch(std::string s) {
        std::cout << s << '\n';
    }
    std::cout << vec.is_empty() << '\n';
    return 0;
}