// виртуальное наследование в проблеме ромба позволяет создать только одну бабушку
//dinamic cast позволяет прыгать с ветки на ветку в ромбе
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x = 0;
    double y = 0;
    Point(double x, double y): x(x), y(y){}
};

double length(Point a, Point b){
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Abstract class
class Shape {
protected:
    std::vector<Point> storage;  // хранилище угловых точек для фигуры
    std::vector<double> mass;
public:
    Shape(std::vector<Point> storage, std::vector<double> mass): storage(storage), mass(mass){}

    virtual double area() const =0;

    virtual double perimeter() const{
        double result = 0;
        for (int i = 0; i < storage.size() - 1; i++){
            result += length(storage[i], storage[i+1]);
        }
        result += length(storage[0], storage[storage.size() - 1]);
        return result;
    };

    virtual Point center() const{
        double x_c = 0;
        double y_c = 0;
        double m = 0;
        for (int i = 0; i < storage.size(); i++){
            x_c += storage[i].x * mass[i];
            y_c += storage[i].y * mass[i];
            m += mass[i];
        }
        Point res(x_c/m, y_c/m);
        return res;
    };
};

class Triangle: public Shape {
public:
    Triangle(std::vector<Point> storage, std::vector<double> mass): Shape(storage, mass){}
    double area() const override{
        double p = this->perimeter()/2;
        double a = length(this->storage[0], this->storage[1]);
        double b = length(this->storage[1], this->storage[2]);
        double c = length(this->storage[0], this->storage[2]);
        return std::sqrt(p*(p-a)*(p-b)*(p-c));
    }
};


class Square: public Shape {
public:
    Square(std::vector<Point> storage, std::vector<double> mass): Shape(storage, mass){}
    double area() const override{
        return length(this->storage[0], this->storage[1]) * length(this->storage[1], this->storage[2]);
    }
};

class Line: public Shape {
public:
    Line(std::vector<Point> storage, std::vector<double> mass): Shape(storage, mass){}
    double perimeter() const override{
        return length(this->storage[0], this->storage[1]);
    }
    double area() const override{
        return 0;
    }
};

int main(){
    Point x0 (1, 1);
    Point x1 (1, 5);
    Point x2 (5, 5);
    Point x3 (1, 5);
    std::vector<Point> v_s = {x0, x1, x2, x3};
    std::vector<double> m_s = {1, 2, 3, 4};

    std::vector<Point> v_t = {x0, x1, x2};
    std::vector<double> m_t = {1, 2, 3};

    std::vector<Point> v_l = {x0, x1};
    std::vector<double> m_l = {1, 2};

    Triangle T(v_t, m_t);
    Line L(v_l, m_l);
    Square S(v_s, m_s);

    std::cout << T.area() << '\n';
    std::cout << T.perimeter() << '\n';
    std::cout << '(' << T.center().x << ',' << T.center().y << ')' << '\n';

    std::cout << "---------------\n" ;

    std::cout << L.area() << '\n';
    std::cout << L.perimeter() << '\n';
    std::cout << '(' << L.center().x << ',' << L.center().y << ')' << '\n';

    std::cout << "---------------\n" ;

    std::cout << S.area() << '\n';
    std::cout << S.perimeter() << '\n';
    std::cout << '(' << S.center().x << ',' << S.center().y << ')' << '\n';

    return 0;
}
