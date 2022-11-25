#include <iostream>
#include <cassert>
#include <vector>

template <typename T>
class Grid final {
public :
    using value_type = T;
    using size_type = unsigned ;
    T * data ; //убрали константность, для того, чтобы можно было объявлять в конструкторе
    size_type const y_size , x_size ;

    Grid (T * data , size_type y_size , size_type x_size) :
            data(data) , y_size(y_size), x_size ( x_size ) { }

    Grid(T const& t): y_size(1), x_size(1) {
        data = new T;
        *data = t;
    }

    Grid(size_type y_size, size_type x_size): y_size(y_size), x_size(x_size){
        data = new T[y_size * x_size];
        T element;
        for (
                auto it = data , end = data + x_size * y_size ;
                it != end; ++it
                ) * it = element;
    }

    Grid(size_type y_size, size_type x_size, T const &t): y_size(y_size), x_size(x_size){
        data = new T[y_size * x_size];
        for (
                auto it = data , end = data + x_size * y_size ;
                it != end; ++it
                ) * it = t;
    }

    Grid (Grid<T> const& other) : y_size(other.get_y_size()), x_size(other.get_x_size()){
        data = new T[y_size * x_size];
        for(size_type i = 0; i < y_size; i++){
            for(size_type j = 0; j < x_size; j++){
                data[j + i * x_size] = other.data[j + i * x_size];
            }
        }
    };

    Grid (Grid<T>&& other): y_size(other.get_y_size()), x_size(other.get_x_size()){
        data = other.data;
        other.data = nullptr;
    };

    Grid<T>& operator=(Grid<T>& rha) {
        //создали временный "переносчик" информации, он удалится (деструктором), как только программа закончит выполнять функцию
        //будем присваивать только если размеры совпадают
        if(this->x_size == rha.get_x_size() && this->y_size == rha.get_y_size()) {
            Grid<T> tmp(rha);
            std::swap(this->data, tmp.data);
        }
        return *this;
    };

    Grid<T>& operator=(Grid<T>&& rha) {
        if(this->x_size == rha.get_x_size() && this->y_size == rha.get_y_size()) {
            Grid<T> tmp(std::move(rha));
            std::swap(this->data, tmp.data);
        }
        return *this;
    };

    T operator() (size_type y_idx, size_type x_idx) const{
        return data[y_idx * x_size + x_idx];
    }

    T& operator() (size_type y_idx, size_type x_idx) {
        return data [ y_idx * x_size + x_idx ] ;
    }

    Grid<T>& operator=(T const&t) {
        for (
                auto it = data , end = data + x_size * y_size ;
                it != end; ++it
                ) * it = t;
        return * this;
    }

    void const print(){
        for (size_type i = 0; i < y_size; i++) {
            for (size_type j = 0; j < x_size; j++)
                std::cout << data[j + i * x_size] << ' ';
            std::cout << '\n';
        }
    }

    size_type get_y_size ( ) const {return y_size;}
    size_type get_x_size ( ) const {return x_size;}

    //возвращаем указатель на начало строки, в которой содержится необходимый нам элемент
    T* operator[](size_t y_idx){
        return data + y_idx * x_size;
    }
    //оператор [], определнный по умолчанию сделает сдвиг на x_idx

    ~Grid(){
        delete[] data;
    }
};

class Point{
    int x;
    int y;
public:
    Point():x(0), y(0){}
    Point(int x, int y): x(x), y(y){}
    void const print (){
        std::cout << '(' << x << ',' << y << ')' << '\n';
    }
    friend std::ostream& operator<<(std::ostream& out, const Point& obj);
};

std::ostream& operator<<(std::ostream& out, const Point& obj){
    return out << '(' << obj.x << ',' << obj.y << ")";
}


template <typename T, typename ...Tail>
class Tensor_Grid final {
private:
    template <typename U> //создали специализацию
    void func(const U & head){
        size.push_back(head);
        ++dim;
    }

    template <typename U, typename ...Tail1>
    void func(const U & head, Tail1... tail){
        size.push_back(head);
        ++dim;
        func(tail...);
    }

public :
    using value_type = T;
    using size_type = unsigned ;
    T * data ;
    std::vector<unsigned> size;
    unsigned dim = 0;

    Tensor_Grid (const T &t, Tail... tail){
        func(tail...);
        size_type length = 1;
        for(size_t i = 1; i < size.size(); i++){
            length *= size[i];
        }
        data = new T[length];
        for (auto it = data , end = data + length ;
             it != end; ++it)
            * it = t;
    }

    Tensor_Grid(Tensor_Grid<T, Tail...> const& other){
        size = other.size; //для вектора определен оператор копирующего присваивания
        size_type length = 1;
        for(size_t i = 1; i < size.size(); i++){
            length *= size[i];
        }
        data = new T[length];
        for (size_t i = 0; i < length; i++)
            data[i] = other.data[i];
    };

    Tensor_Grid<T, Tail...>& operator=(Tensor_Grid<T, Tail...>& rha) {
        bool flag = true;
        for (size_t i = 0; i < size.size(); i++){
            if(size[i] != rha.size[i])
                flag = false;
        }
        if(flag) {
            Tensor_Grid<T, Tail...> tmp(rha);
            std::swap(this->data, tmp.data);
        }
        return *this;
    };

    T operator() (const size_type* idxes) const{
        size_type length = 1;
        for(size_t i = 1; i < dim; i++){
            length *= size[i];
        }
        size_type idx = 0;
        for(size_t i = 0; i < dim; i++){
            length = length / size[i];
            idx += idxes[i]*length;
        }
        return data[idx];
    }

    ~Tensor_Grid(){
        delete[] data;
    }

};

int main(){
    Point a (2, 4);
    a.print();
    std::cout << " -----tests of 3 extra constructors ----\n";
    Grid<Point> g1 (a);
    g1.print();
    Grid<Point> g2 (3, 2);
    g2.print();
    Grid<Point> g3 (3, 2, a);
    g3.print();
    std::cout << " -----tests of five----\n";
    Grid<Point> g4 (g3);
    g4.print();
    std::cout << "----------\n";
    Grid<Point> g5 (std::move(g3));
    g5.print();
    std::cout << g3.data << '\n'; //там действительно остался nullptr
    std::cout << "----------\n";
    g5 = g2;
    g5.print();
    std::cout << "----------\n";
    Grid<Point> g6 (3, 2, a);
    g6 = std::move(g5);
    g6.print();
    std::cout << g5.data << '\n'; //там действительно остался nullptr

    Grid<float> g (3,2,0.0f) ;
    assert (3 == g.get_y_size( ));
    assert (2 == g.get_x_size( ));
    std::cout << "----------\n";

    //своя проверка оператора [][], у лектора код с ошибками, не хочу разбираться
    int* array = new int[6];
    array[0] = 10;
    array[1] = -2;
    array[2] = 4;
    array[3] = 10;
    array[4] = 11;
    array[5] = 220;
    Grid<int> grid (array,2, 3);
    grid.print();
    std::cout << grid[1][2] << '\n';

    std::cout << "----------!!!!!----------\n";
    Tensor_Grid<int, unsigned, unsigned, unsigned> Tens(5, 2, 2, 2); //в примере с семинара не нужно было указывать типы в tail

    unsigned idxes[3] = {0,1,1};
    std::cout << Tens(idxes) << '\n';

    Tensor_Grid<int, unsigned, unsigned, unsigned> Tens1(Tens);
    std::cout << Tens1(idxes) << '\n';

    Tensor_Grid<int, unsigned, unsigned, unsigned> Tens2(3, 2,2,2);
    Tens2 = Tens;
    std::cout << Tens2(idxes);

}
