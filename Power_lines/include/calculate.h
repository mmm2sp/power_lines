#ifndef POWER_LINES_CALCULATE_H
#define POWER_LINES_CALCULATE_H

template <typename U>
class Body{
    //coordinates
    double x;
    double y;
public:
    Body(double x, double y);
    virtual U field_calc(double x, double y) const = 0;
    double get_x() const;
    double get_y() const;
};

template <typename U>
U res_field_calc(std::vector<Body<U>*>& bodies, double x, double y);

class vec{
    double x;
    double y;
public:
    vec();
    vec(double x,double y);
    vec operator *(double k);
    vec operator +=(vec other);
    vec operator -=(vec other);
    bool operator ==(vec other) const;
    bool operator !=(vec other) const;
    vec norm() const;
    double get_x() const;
    double get_y() const;
    friend std::ostream& operator<<(std::ostream& out, const vec& obj);
};

std::vector<vec> points_for_line(std::vector<Body<vec>*>& bodies, vec start, double width, double height, bool forward);

std::vector<std::vector<vec>> all_lines(std::vector<Body<vec>*>& charges, unsigned density_factor, double width, double height);

class Charge final: public Body<vec> {
    //value of charge
    double q;
public:
    Charge();
    Charge(double x, double y, double q);
    vec field_calc(double a, double b) const override;
    double get_q() const;
};

double distance(double x1, double x2, double y1, double y2);

template <typename U>
double find_step(std::vector<Body<U>*>& bodies, double width);

#endif //POWER_LINES_CALCULATE_H
