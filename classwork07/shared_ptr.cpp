#include <iostream>
#include <utility>

template <typename T>
class shared_ptr {
public:
    shared_ptr(T* ptr) : ptr(ptr), cptr(new ControlBlock<T>({ 1, *ptr })) { }

    shared_ptr(const shared_ptr<T>& other) : ptr(other.ptr), cptr(other.cptr) {
        ++(cptr->counter);
    }

    shared_ptr(shared_ptr<T>&& other) : ptr(other.ptr), cptr(other.cptr) {
        other.ptr = nullptr;
        other.cptr = nullptr;
    }

    template <typename T, typename... Args>
    friend shared_ptr<T> make_shared(Args&&... args);

    size_t use_count() const {
        return cptr->counter;
    }

    ~shared_ptr() {
        if (cptr != nullptr) {
            if (cptr->counter == 1) {
                std::cout << "ptr was delited \n";
                delete[] ptr;
                delete cptr;
            }
            else
                --(cptr->counter);
        }
    }

    T operator *() {
        return cptr->object;
    }

private:
    template <typename T>
    struct ControlBlock {
        size_t counter;
        T object;
    };

    T* ptr = nullptr;
    ControlBlock<T>* cptr = nullptr;
};

template <typename T, typename U, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto ptr = new T(std::forward<U>(args)...);
    return shared_ptr<T>(ptr);
}

class Point {
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}

    void Get_x() {
        std::cout << x << '\n';
    }

    void Get_y() {
        std::cout << y << '\n';
    }
};

int main() {
    shared_ptr<Point> a_shared = make_shared<Point, int>(10, 3);
    std::cout << a_shared.use_count() << '\n';
    shared_ptr<Point> b_shared = shared_ptr<Point>(std::move(a_shared));
    std::cout << b_shared.use_count() << '\n';
    Point p = *b_shared;
    p.Get_x();
    return 0;
}