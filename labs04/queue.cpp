#include <iostream>
#include <vector>

template <typename T>
struct Comparator {
    virtual bool operator ()(T const &, T const &) const = 0 ;
};

template <>
struct Comparator<int> {
    bool operator ()(int const &lha , int const &rha ) const{
        return lha > rha;
    }
};

template <>
struct Comparator<double> {
    bool operator ()(double const &lha , double const &rha ) const{
        return lha > rha;
    }
};

template <typename T>
class PriorityQueue {
    Comparator<T> comp;
    std::vector<T> queue;
public:
    PriorityQueue(const Comparator<T> & compar){
        comp = compar;
        std::vector<T> empty;
        queue = empty;
    }
    void push(T element){
        bool flag = false;
        for(int i = 0; i < queue.size(); i++){
            if(comp(element, queue[i])){
                auto it = queue.begin();
                queue.insert(std::next(it, i), element);
                flag = true;
                break;
            }
        }
        if (!flag){
            queue.push_back(element);
        }
    }
    T peek(){
        return queue[0];
    }
    void poll(){
        if (queue.size() == 0) {
            std::cout << '\n';
            std::cerr << "There is no elements in queue";
            return;
        }
        for(int i = 0; i < queue.size() - 1; i++){
            queue[i] = queue[i + 1];
        }
        queue.pop_back();
    }

    bool is_empty(){
        return queue.empty();
    }

    void free(){
        queue.clear();
    }
};

int main(){
    Comparator<double> comp;
    PriorityQueue<double> Q (comp);
    Q.push(4.21);
    Q.push(5.33);
    Q.push(2.22);
    Q.push(10.33);
    std::cout << Q.peek() << '\n';
    Q.poll();
    std::cout << Q.peek() << '\n';
    Q.poll();
    std::cout << Q.peek() << '\n';
    Q.poll();
    std::cout << Q.peek() << '\n';
    Q.poll();
    std::cout << Q.is_empty();
    return 0;
}