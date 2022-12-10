#include <iostream>
#include <cmath>
#include <vector>
#include "calculate.h"

//обобщенная часть
template <typename U>
double Body<U>::get_x() const {return x;}

template <typename U>
double Body<U>::get_y() const {return y;}

template<typename U>
Body<U>::Body(double x, double y): x(x), y(y){}

template <typename U>
U res_field_calc(std::vector<Body<U>*>& bodies, double x, double y){
    U field;
    for (auto && item : bodies){
        field += item->field_calc(x, y);
    }
    return field;
}

double distance(double x1, double x2, double y1, double y2){
    return pow((pow(x1 - x2, 2) + pow(y1 - y2, 2)), 0.5);
}

//дописать впоследствии
template <typename U>
double find_step(std::vector<Body<U>*>& bodies, double width){
    double min_distance = width;
    for (unsigned i = 0; i < bodies.size(); ++i){
        for (unsigned j = i + 1; j < bodies.size(); ++j){
            double dist = distance(bodies[i]->get_x(), bodies[j]->get_x(), bodies[i]->get_y(), bodies[j]->get_y());
            if(dist < min_distance){
                min_distance = dist;
            }
        }
    }
    return std::min(min_distance/1000, 1.0); //для предотвращения "перепрыжек" (см строку с комментарием со "*")
}

//2d vector
vec::vec(): x(0), y(0) {}

vec::vec(double x,double y): x(x), y(y) {}

vec vec::operator +=(vec other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

vec vec::operator -=(vec other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

vec vec:: operator *(double k){
    this->x *= k;
    this->y *= k;
    return *this;
}

bool vec:: operator ==(vec other) const{
    return other.get_x() == this->get_x() && other.get_y() == this->get_y();
}

bool vec::operator!=(vec other) const {
    return (x - other.get_x()) > 0.00001 || (y - other.get_y()) > 0.00001;
}

vec vec::norm() const {
    return (vec(x / pow(x*x + y*y, 0.5), y / pow(x*x + y*y, 0.5)));
}

double vec::get_x() const {return x;}

double vec::get_y() const {return y;}

std::ostream &operator<<(std::ostream &out, const vec &obj) {
    return out << '(' << obj.get_x() << ", " << obj.get_y() << ' ' << ')';
}

//forward показывает направление посториения линии, неоюходим, чтобы чертить линии для отрицательных зарядов
std::vector<vec> points_for_line(std::vector<Body<vec>*>& bodies, vec start, double width, double height, bool forward) {
    double step = find_step(bodies, width);
    std::vector<vec> result;
    vec current = start;
    vec pre_current = start += vec(3,3); //просто какой-то вектор, не равный start

    while(true){
        unsigned counter = 0;
        for (auto && body: bodies){
            if(distance(body->get_x(), current.get_x(), body->get_y(), current.get_y()) < 1){ //* 1 пиксель - расстояние, меньшее, чем радиус отображаемого объекта
                return result;
            }
            if(std::abs(current.get_x()) > width || std::abs(current.get_y()) > height){
                return result;
            }
        }
        result.push_back(current);
        pre_current = current;
        if(forward) {
            current += res_field_calc(bodies, current.get_x(), current.get_y()).norm() * step;
            ++counter;
        }else{
            current -= res_field_calc(bodies, current.get_x(), current.get_y()).norm() * step;
            ++counter;
        }
        //проверка коллизии (случай, когда линия не сдвигается; точка ходит вперед-назад) считаем скалярное произведение
        if(current.get_x() * pre_current.get_x() + current.get_y() * pre_current.get_y() <= 0){
            result.clear();
            return result;
        }
        if(counter > 10000*std::max(width, height)){
            throw std::runtime_error("Unexpected collision situation");
        }
    }
}

std::vector<std::vector<vec>> all_lines(std::vector<Body<vec>*>& charges, unsigned density_factor, double width, double height){
    std::vector<std::vector<vec>> lines;
    for(auto && flag: {true, false}) {
        for (auto &&charge: charges) {
            for(unsigned i = 0; i < density_factor; ++i) {
                double x_start = charge->get_x() + std::cos(i * 2 * M_PI/density_factor) + 0.1*std::sin(i * 2 * M_PI/density_factor);
                double y_start = charge->get_y() - std::sin(i * 2 * M_PI/density_factor) + 0.1*std::cos(i * 2 * M_PI/density_factor);
                try {
                    std::vector<vec> new_line = points_for_line(charges, vec(x_start, y_start), width, height, flag);
                    lines.push_back(new_line);
                } catch (std::runtime_error &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }
    return lines;
}

//частный случай
Charge::Charge(): Body(0, 0), q(0) {}

Charge::Charge(double x, double y, double q): Body(x,y), q(q) {}

vec Charge::field_calc(double a, double b) const{
    return vec(q*(a-this->get_x()) / pow((a-this->get_x())*(a-this->get_x()) + (b-this->get_y())*(b-this->get_y()),
            3.f/2.f), q*(b-this->get_y()) / pow((a-this->get_x())*(a-this->get_x()) + (b-this->get_y())*(b-this->get_y()),
                    3.f/2.f));
}

double Charge::get_q() const {
    return q;
}