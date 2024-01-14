#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
 
class SimpleRNG {
private:
    double a, c, m;
    double state;
 
public:
    SimpleRNG(double a, double c, double m, double initialState = 0.0) : a(a), c(c), m(m), state(initialState) {}
 
    void reset(double initialState = 0.0) {
        state = initialState;
    }
 
    class Iterator;
 
    Iterator begin() {
        return Iterator(this);
    }
 
    Iterator end(double eps = 0.05) {
        SimpleRNG endRNG = *this;
        endRNG.state = -1.0; // Используем состояние, которое не совпадает с текущим состоянием
        Iterator endIterator(&endRNG);
 
        while (std::fabs(endIterator.rng->state - state) >= eps) {
            ++endIterator;
        }
 
        return endIterator;
    };
 
    class Iterator : public std::iterator<std::input_iterator_tag, double> {
    private:
        SimpleRNG* rng;
 
    public:
        friend class SimpleRNG;
 
        explicit Iterator(SimpleRNG* rng) : rng(rng) {}
 
        Iterator& operator++() {
            rng->state = std::fmod(rng->a * rng->state + rng->c, rng->m);
            return *this;
        }
 
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
 
        bool operator==(const Iterator& other) const {
            return std::fabs(rng->state - other.rng->state) < 0.05; // Используем eps = 0.05
        }
 
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
 
        double operator*() const {
            return rng->state;
        }
    };
};
 
int main() {
    SimpleRNG generator(5, 0.2, 1);
    generator.reset(0.4);
    std::vector<double> vec;
    std::copy(generator.begin(), generator.end(0.5), std::back_inserter(vec));
 
    for (auto x : vec)
        std::cout << x << ' ';
 
    return 0;
}
