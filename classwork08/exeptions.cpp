#include <iostream>
//спросить про делит

struct base_exception {
    virtual std::string what() = 0;
};

struct math_exception : public base_exception {
    std::string what() {
        return "ziro division error";
    }
};

struct invalid_argument : public base_exception {
    std::string what() {
        return "invalid argument error";
    }
};

double inverse(double x) {
    if (x == 0)
        throw math_exception();
    return 1. / x;
}

double root(double x) {
    if (x < 0)
        throw invalid_argument();
    return std::sqrt(x);
}

int main()
{
    try {
        inverse(0);
    }
    catch(math_exception a){
        std::cout << a.what() << '\n';
    }
    try {
        root(-5);
    }
    catch (invalid_argument a) {
        std::cout << a.what() << '\n';
    }
    return 0;
}
