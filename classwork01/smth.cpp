#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>

void swap(void* lha, void* rha, std::size_t type_size) {
    void* tmp = malloc(type_size);
    std::memcpy(tmp, lha, type_size);
    std::memcpy(lha, rha, type_size);
    std::memcpy(rha, tmp, type_size);
    free(tmp);
}

int min(void* arr, int arr_size, int type_size, int (*compare)(void *, void *)){
    auto min = arr;
    for(int i = 1; i < arr_size; i++){
        if(compare(min, (char *)arr + type_size*i) > 0){
            min = (char *)arr + type_size*i;
        }
    }
    int idx = int((char *) min - (char *) arr)/type_size;
    return idx;
}

int max(void* arr, int arr_size, int type_size, int (*compare)(void *, void *)){
    auto max = arr;
    for(int i = 1; i < arr_size; i++){
        // поменяли порядок аргументов при передачи в функцию compare
        if(compare((char *)arr + type_size*i, max) > 0){
            max = (char *)arr + type_size*i;
        }
    }
    int idx = int((char *) max - (char *) arr)/type_size;
    return idx;
}

int int_compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}

int short_int_compare(void* a, void* b){
    return *(short*)a - *(short*)b;
}

void Heapify(void* arr_, int index, int left, int right, int type_size, int (*compare)(void *, void *)){
    void* arr = (char*)arr_ + left * type_size;
    int size = right - left;
    if (2*index + 1 > size)
        return;
    void* l = (char*) arr + 2*index*type_size + type_size;
    if (2*index + 2 > size) {
        if (compare((char*)arr + index*type_size, l) < 0)
            swap((char*)arr + index*type_size, l, type_size);
        return;
    }
    void* r = (char*) arr + 2*index*type_size + 2*type_size;
    if(compare((char*)arr + index*type_size, l) < 0) {
        if (compare(l, r) >= 0) {
            swap((char*)arr + index*type_size, l, type_size);
            Heapify(arr, 2 * index + 1, left, right, type_size, compare);
        }
    }
    if(compare((char*)arr + index*type_size, r) < 0){
        if(compare(l, r) < 0){
            swap((char*)arr + index*type_size, r, type_size);
            Heapify(arr, 2 * index + 2, left, right, type_size, compare);
        }
    }
    if (compare((char*)arr + index*type_size, l) >= 0 && compare((char*)arr + index*type_size, r) >= 0)
        return;
}

void BuildHeap(void* arr_, int left, int right, int type_size, int (*compare)(void *, void *)){
    void* arr = (char*)arr_ + left * type_size;
    int size = right - left;
    for (int i = size/2; i>=0; i--)
        Heapify(arr, i, left, right, type_size, compare);
}

void qsort(void* arr_, int left, int right, int type_size, int (*compare)(void *, void *)){
    void* arr = (char*)arr_ + left * type_size;
    BuildHeap(arr, left, right, type_size, compare);
    int HeapSize = right - left;
    int size = right - left;
    for(int i = 0; i < size; i++){
        swap(arr, (char*) arr + HeapSize * type_size, type_size);
        HeapSize--;
        Heapify(arr, 0, 0, HeapSize - 1, type_size, compare);
    }
}

int main(){

    int a = 5;
    int b = 7;
    swap(&a, &b, sizeof(int));
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << "------------" << std::endl;

    int array[6] = {10, 15, 1,-3, -5, -10};
    std::cout << min(array, 5, sizeof(int), int_compare) << std::endl;
    std::cout << max(array, 5, sizeof(int), int_compare) << std::endl;

    std::cout << "------------" << std::endl;

    int (*operations[2])(void*, void*) = {int_compare, short_int_compare};
    qsort(array, 0, 5, sizeof(int), operations[1]);
    for(int i = 0; i < 6; i++)
        std::cout << array[i] << ' ';

    std::cout << std::endl;
    std::cout << "------------" << std::endl;

    std::cout << "size char: " << sizeof(char)*8 << std::endl;
    std::cout << "min char: " << std::numeric_limits<char>::min() << std::endl;
    std::cout << "max char: " << std::numeric_limits<char>::max() << std::endl;

    std::cout << "size short int: " << sizeof(short int)*8 << std::endl;
    std::cout << "min short int: " << std::numeric_limits<short int>::min() << std::endl;
    std::cout << "max short int: " << std::numeric_limits<short int>::max() << std::endl;

    std::cout << "size int: " << sizeof(int)*8 << std::endl;
    std::cout << "min int: " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "max int: " << std::numeric_limits<int>::max() << std::endl;

    std::cout << "size float: " << sizeof(float)*8 << std::endl;
    std::cout << "min float: " << std::numeric_limits<float>::min() << std::endl;
    std::cout << "max float: " << std::numeric_limits<float>::max() << std::endl;

    std::cout << "size long int: " << sizeof(long int)*8 << std::endl;
    std::cout << "min long int: " << std::numeric_limits<long int>::min() << std::endl;
    std::cout << "max long int: " << std::numeric_limits<long int>::max() << std::endl;

    std::cout << "size double: " << sizeof(double)*8 << std::endl;
    std::cout << "min double: " << std::numeric_limits<double>::min() << std::endl;
    std::cout << "max double: " << std::numeric_limits<double>::max() << std::endl;
    return 0;
}