#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include "calculate.h"

template <class T, class U>
void AssertEqual(T &t, U &u, const std::string &hint) {
    if (t != u)
    {
        std::cout << "Assertion failed: "  << t << ' ' <<  "!=" << ' ' << u << " Hint: " << hint << "\n";
        throw std::runtime_error(hint);
    }
}

template <class TestFunc, class ...Tail>
void RunTest(TestFunc func, Tail... tail)
{
    try
    {
        func(tail...);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << " fail: " << e.what() << std::endl;
    }
}

int main() {
    using field_type = vec;
    Charge q1 = Charge(0, 2, 3);
    Charge q2 = Charge(1, 4, 4);
    std::vector<Body<field_type>*> charges = {&q1, &q2};
    vec E = res_field_calc<field_type> (charges, 0, 3);
    RunTest(AssertEqual<vec, vec>, E, vec(-1.41421, 1.58579), "field calculation");
    RunTest(AssertEqual<vec, vec>, E.norm(), vec(-0.665579, 0.746327), "normalization of vector");
    RunTest(AssertEqual<double, double>, std::round(find_step(charges, 500)*10000)/10000, std::round(0.00223607*10000)/10000, "find step");
    return 0;
}