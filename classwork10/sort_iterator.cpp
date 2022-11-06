#include <iostream>
#include <algorithm>
#include <type_traits>

//T - принимает 2 значения: Descending, Ascending

struct Descending {
    int a;
};

struct Ascending {
    int a;
};

template <typename T, typename U>
struct SortIterator {

    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = U;
    using pointer = U*;
    using reference = U&;

    SortIterator(pointer ptr_1, pointer ptr_2) {
        len = ptr_2 - ptr_1;
        if (len != 0) {
            data = new value_type[len];
            std::copy(ptr_1, ptr_2, data);
            if (std::is_same<T, Ascending>::value)
                std::sort(ptr_1, ptr_2);
            if (std::is_same<T, Descending>::value)
                std::sort(ptr_1, ptr_2, std::greater<value_type>());
            begin = data;
        }
        else {
            begin = ptr_1;
        }
    }

    SortIterator(pointer ptr_1) : begin(ptr_1) {}

    // pre increment
    SortIterator& operator++() {
        if ((data + len) - begin >= 1)
            begin++;
        else
            len = 0;
        return *this;
    }
    // post increment
    SortIterator operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    reference operator*() const {
        return *begin;
    }
    pointer operator->() {
        return begin;
    }

    friend bool operator!=(const SortIterator& a, const SortIterator& b) {
        return a.len != 0;
    }

    ~SortIterator() {
        delete[] data;
    }

private:
    pointer begin;
    int len = 0;
    pointer data = nullptr;
};

int main()
{
    int input[5] = { 5,2,1,2,2 };
    int output[5] = { 0,0,0,0,0 };
    int* input_ptr = input;
    int* output_ptr = output;

    std::copy(SortIterator<Descending, int>(input_ptr, input_ptr + 5),
              SortIterator<Descending, int>(input_ptr + 5),
              output_ptr);

    for (int i = 0; i < 5; i++)
        std::cout << output[i] << ' ';
}

