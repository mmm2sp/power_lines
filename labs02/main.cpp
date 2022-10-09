#include <iostream>
#include <algorithm>
#include <set>
#include <random>

// сделаем новый класс State и определим виртуальню функцию contains. Это рацонально, так как этот метод содежится
// в каждом виде State (в них он будет переопределен)
class State{
public:
    virtual bool contains(int s) const=0;
};

class DiscreteState: public State{
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const override{
        return s == state;
    }
};

class SegmentState: public State {
private:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};

class SetState: public State {
private:
    std::set<int> states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const override{
        return states.count(s) > 0;
    }

    //возможный вариант создавать новые объекты на основе старых
    SetState& operator+(const SetState& other){
        std::set<int> new_states;
        std::set_union(states.begin(), states.end(), other.states.begin(), other.states.end(), new_states.begin());
        SetState res (new_states);
        return res;
    }
};

//новый составной класс
class Set_Discrete: public State{
private:
    SetState ss;
    DiscreteState s;
public:
    Set_Discrete(DiscreteState s, SetState ss): ss(ss), s(s){}

    bool contains(int t) const override{
        return ss.contains(t) && s.contains(t); //если точка и там и там
    }
};

class Set_Segment: public State{
private:
    SetState ss;
    SegmentState s;
public:
    Set_Segment(SegmentState s, SetState ss): ss(ss), s(s){}

    bool contains(int t) const override{
        return ss.contains(t) && s.contains(t); //если точка и там и там
    }
};

class ProbabilityTest {
private:
    int test_min, test_max;

public:
    unsigned seed;
    unsigned test_count;
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    // вызываем оператор по метке родительского класса -> получаем "обобщение по классу" (типу)
    float operator()(State const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

};

int main(int argc, const char * argv[]) {
    DiscreteState d(1); // 1 элемент
    SegmentState s(0,10); // 11 элементов
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99}); // 10 элементов
    ProbabilityTest pt(5,0,100,5); // 101 элемент

    int n = 20;
    int step = 10000;
    int N = 100;
    float* discrete_data = new float [n];
    float* segment_data = new float [n];
    float* set_data = new float [n];
    int idx = 0;

    for (int test_counts = step; test_counts <= step*n; test_counts += step){
        pt.test_count = test_counts;
        float Discrete_sum = 0;
        float Segment_sum = 0;
        float Set_sum = 0;
        for (int seed = 10; seed <= N * 10; seed += 10){
            pt.seed = seed;
            Discrete_sum += pt(d);
            Segment_sum += pt(s);
            Set_sum += pt(ss);
        }
        discrete_data[idx] = Discrete_sum/float(N);
        segment_data[idx] = Segment_sum/float(N);
        set_data[idx] = Set_sum/float(N);
        idx++;
    }

    for(int i = 0; i < n; i++){
        std::cout << set_data[i] << ", ";
    }

    std::cout << std::endl;

    for(int i = 1; i <= n; i++) {
        std::cout << step * i << ", ";
    }

    delete[] discrete_data;
    delete[] segment_data;
    delete[] set_data;
    return 0;
}
//Условный вывод: результаты сошлись с теорией. Вероятность не зависит от расположения элементов, это показали графики
//set и segment (в первом случае элементы выбраны рандомно, во втором они идут подряд), в обоих случаях результат подчиняется
//теоретичесой формуле.


