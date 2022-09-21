#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
    unsigned long long x , y; //убрал константность

    Point ( unsigned long long x , unsigned long long y ) :
            x (x), y (y) { }

    Point minx ( Point const &rha ) const {
        return Point ( rha.x < x ? rha.x : x , y ) ;
    }

    Point miny ( Point const &rha ) const {
        return Point ( x , rha.y < y ? rha.y : y ) ;
    }

    Point maxx ( Point const &rha ) const {
        return Point ( rha.x > x ? rha.x : x , y ) ;
    }

    Point maxy ( Point const &rha ) const {
        return Point ( x , rha.y > y ? rha.y : y ) ;
    }

    void print ( ) const {
        std::cout << '(' << x << ',' << y << ')' ;
    }
};


class Rectangle: public Point {

public:
    Rectangle() : Point(0, 0) {}

    Rectangle(Point const & p): Point(p.x, p.y) {}

    Rectangle operator*(Rectangle const &rha) const{
        Point p(minx(rha).x, miny(rha).y);
        Point const & a = p;
        Rectangle res (a);
        return res;
    }

    Rectangle operator+(Rectangle const &rha) const{
        Point p(maxx(rha).x, maxy(rha).y);
        Point const & a = p;
        Rectangle res (a);
        return res;
    }
};

int main(){

    /*
    Point p1(1, 4);
    Rectangle a(p1);
    Point p2(5,2);
    Rectangle b(p2);
    Rectangle sum = a + b;
    Rectangle mult = a * b;
    sum.print();
    mult.print();
     */


    //программа работает для координат меньше 10, иначе сложно считывать
    string str, expression;
    getline ( cin , str);
    remove_copy(str.begin(), str.end(), back_inserter(expression), ' ');
    int l = expression.size();
    for (int i = 0; i < l; i++){
        if (expression[i] == '*') {
            int y1 = int(expression[i - 2]) - 48;
            int x1 = int(expression[i - 4]) - 48;
            Point p1(x1, y1);
            int x2 = int(expression[i + 2]) - 48;
            int y2 = int(expression[i + 4]) - 48;
            Point p2(x2, y2);
            Rectangle a (p1);
            Rectangle b (p2);
            Rectangle res = a*b;
            expression[i] = '+';
            expression[i - 2] = char(res.y + 48);
            expression[i - 4] = char(res.x + 48);
            expression[i + 2] = char(res.x + 48);
            expression[i + 4] = char(res.y + 48);
        }
    }
    int x0 = int(expression[1]) - 48;
    int y0 = int(expression[3]) - 48;
    Point p0 (x0, y0);
    Rectangle res (p0);
    for (int i = 0; i < l; i++){
        if (expression[i] == '+') {
            int x2 = int(expression[i + 2]) - 48;
            int y2 = int(expression[i + 4]) - 48;
            Point p2(x2, y2);
            Rectangle a(p2);
            res = res + a; // константность убрана для этого
        }
    }
    res.print();
    return 0;
}