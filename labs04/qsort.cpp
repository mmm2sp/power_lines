#include <iostream>
using namespace std;

template <typename T>
struct Comparator {
    virtual bool operator ()(T const &, T const &) const = 0 ;
};

//создадим специализацию
template <>
struct Comparator<int> {
    bool operator ()(int const &lha , int const &rha ) const{
        return lha > rha;
    }
};

template <typename T>
void Heapify(T* array, long index, long size, Comparator<T> comp){
    if (2*index + 1 > size)
        return;
    T left = array[2*index + 1];
    if (2*index + 2 > size){
        if (comp(left, array[index]))
            swap(array[index], array[2 * index + 1]);
        return;
    }
    T right = array[2*index + 2];
    if (comp(left, array[index])) {
        if (!comp(right, left)) {
            swap(array[index], array[2 * index + 1]);
            Heapify(array, 2 * index + 1, size, comp);
        }
    }
    if (comp(right, array[index])) {
        if (comp(right, left)) {
            swap(array[index], array[2 * index + 2]);
            Heapify(array, 2 * index + 2, size, comp);
        }
    }
    if (!(comp(left, array[index])) && !(comp(right, array[index])))
        return;
}

template <typename T>
void BuildHeap(T* array, long size, Comparator<T> comp){
    for (long i = size/2; i >= 0; i--)
        Heapify(array, i, size, comp);
}

template <typename T>
void HeapSort(T* array, long size, Comparator<T> comp){
    BuildHeap(array, size, comp);
    long HeapSize = size;
    for (long i = 0; i < size; ++i){
        swap(array[0], array[HeapSize]);
        HeapSize--;
        Heapify(array, 0, HeapSize, comp);
    }
}

int main(){
    Comparator<int> comp1;
    int const N = 6;
    int array[N] = {100, -50, 200 ,6, 40, 1};
    HeapSort<int>(array, 6, comp1);
    for (int i = 0; i < N; i++)
        cout << array[i] << ' ';
    cout << endl;

    return 0;
}
