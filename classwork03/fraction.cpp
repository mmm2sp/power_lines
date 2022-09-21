#include <iostream>

class Fraction {
public:
    friend std::ostream& operator<<(std::ostream& out, const Fraction& obj);  // Оператор вывода << "числитель знаминатель"
    friend std::istream& operator>>(std::istream& is, Fraction& obj);  // Оператор ввода >> числитель >> знаминатель

    Fraction& operator+=(const Fraction& other){
        if ((this->denominator) == (other.denominator)) {
            this->numerator += other.numerator;
        } else {
            this->numerator = (this->numerator) * (other.denominator)
                              + (this->denominator) * (other.numerator);
            this->denominator = (this->denominator) * (other.denominator);
        }
        return *this;
    }

    Fraction& operator-=(const Fraction& other){
        if ((this->denominator) == (other.denominator)) {
            this->numerator -= other.numerator;
        } else {
            this->numerator = (this->numerator) * (other.denominator)
                              - (this->denominator) * (other.numerator);
            this->denominator = (this->denominator) * (other.denominator);
        }
        return *this;
    }

    Fraction& operator*=(const Fraction& other){
        this->numerator *= other.numerator;
        this->denominator *= other.denominator;
        return *this;
    }

    /* не понял, что можно написать с такой сигнатурой
     * friend намекает на объявление оператора вне класса, но вне класса нельзя использовать this, нужно 2 аргумента,
     * поэтому объявил операторы вне класса, но с 2-мя параметрами
    friend Fraction operator+(const Fraction& other);
    friend Fraction operator-(const Fraction& other);
    friend Fraction operator*(const Fraction& other);
     */

    Fraction& operator++(){
        return *this += 1;
    }

    // вроде и ++a и a++ должны поменять само a
    Fraction operator++(int){
        Fraction res = *this;
        ++(res);
        *this = res;
        return *this;
    }

    Fraction& operator--(){
        return *this -= 1;
    }

    Fraction operator--(int){
        Fraction res = *this;
        --(res);
        *this = res;
        return *this;
    }

    Fraction(int numerator, int denominator): numerator(numerator), denominator(denominator) {}

    Fraction(int numerator): Fraction(numerator, 1){}

    Fraction(): Fraction(1, 1) {}

    Fraction(const Fraction& other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }

    void fracSimplify() {  // Сокращает дробь по возможности
        for(int i = 2; i <= numerator ; i ++){
            if(numerator % i == 0){
                if (denominator % i ==0){
                    numerator = numerator / i;
                    denominator = denominator / i;
                }
            }
        }
    }

    double calc() const {  // Возвращает значение дроби в десятичном виде
        return (double(numerator) / double(denominator));
    }

    int getNumerator() const {  // Возвращает значение числителя
        return numerator;
    }

    int getDenominator() const {  // Возвращает знамечение знаменателя
        return  denominator;
    }

private:
    int numerator;
    int denominator;
};

std::ostream& operator<<(std::ostream& out, const Fraction& obj){
    return out << obj.numerator << '/' << obj.denominator; // can access private member Y::data
}

std::istream& operator>>(std::istream& is, Fraction& obj){
    return is >> obj.numerator >> obj.denominator;
}

Fraction operator+(const Fraction& lha, const Fraction& rha) {
    Fraction sum = lha;
    sum += rha;
    return sum;
}

Fraction operator-(const Fraction& lha, const Fraction& rha) {
    Fraction diff = lha;
    diff -= rha;
    return diff;
}

Fraction operator*(const Fraction& lha, const Fraction& rha) {
    Fraction mult = lha;
    mult *= rha;
    return mult;
}

int main(){
    Fraction a (45, 15);
    a.fracSimplify();
    std::cout << a << std::endl;
    std::cout << "-----------" << std::endl;

    Fraction b (2, 4);
    (a *= b).fracSimplify();
    std::cout << a << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << ++a << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << a++ << std::endl;

    std::cout << "-----------" << std::endl;

    std::cout << a * b << std::endl;
}
