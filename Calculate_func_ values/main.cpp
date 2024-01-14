#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
 
class Function {
public:
    virtual double calc(double x) const = 0;
    virtual ~Function() = default;
};
 
class QuadraticFunction : public Function {
private:
    double a, b, c;
 
public:
    QuadraticFunction(double a, double b, double c) : a(a), b(b), c(c) {}
 
    double calc(double x) const override {
        return a * x * x + b * x + c;
    }
};
 
class AbsFunction : public Function {
private:
    double a, b;
 
public:
    AbsFunction(double a, double b) : a(a), b(b) {}
 
    double calc(double x) const override {
        return a * std::abs(x) + b;
    }
};
 
class CosineFunction : public Function {
private:
    double a, b, c, d;
 
public:
    CosineFunction(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
 
    double calc(double x) const override {
        return a * std::cos(b * x + c) + d;
    }
};
 
 
class FunctionCalculation {
private:
    const Function& func;
    double start;
    double end;
    double step;
 
public:
    FunctionCalculation(const Function& func, double start, double end, double step)
        : func(func), start(start), end(end), step(step) {}
 
    std::vector<double> yValues() const {
        std::vector<double> result;
        for (double x = start; x <= end; x += step) {
            result.push_back(func.calc(x));
        }
        return result;
    }
 
    std::vector<double> xValues() const {
        std::vector<double> result;
        for (double x = start; x <= end; x += step) {
            result.push_back(x);
        }
        return result;
    }
 
    std::vector<std::pair<double, double>> Values() const {
        std::vector<std::pair<double, double>> result;
        for (double x = start; x <= end; x += step) {
            result.push_back({ x, func.calc(x) });
        }
        return result;
    }
 
    std::vector<std::pair<double, double>> ValuesAt(double x1, double x2) const {
        if (x1 < start || x2 > end) {
            throw std::out_of_range("ValuesAt: One or more values are out of range.");
        }
 
        std::vector<std::pair<double, double>> result;
        for (double x = x1; x <= x2; x += step) {
            result.push_back({ x, func.calc(x) });
        }
        return result;
    }
 
    void saveCsv(const std::string& filename, bool addHeaders = false) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("saveCsv: Unable to open file.");
        }
 
        if (addHeaders) {
            file << "x,y\n";
        }
 
        for (double x = start; x <= end; x += step) {
            file << x << ',' << func.calc(x) << '\n';
        }
 
        file.close();
    }
 
    friend std::ostream& operator<<(std::ostream& os, const FunctionCalculation& calc) {
        for (double x = calc.start; x <= calc.end; x += calc.step) {
            os << "{" << x << "," << calc.func.calc(x) << "} ";
        }
        return os;
    }
};
 
int main() {
    QuadraticFunction quadFunc(1, 2, 1);
    FunctionCalculation quadCalc(quadFunc, -5, 5, 1);
    std::cout << "Quadratic Function Values: " << quadCalc << std::endl;
 
    try {
        auto valuesOutOfRange = quadCalc.ValuesAt(-10, 10);
    }
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
 
 
    quadCalc.saveCsv("quadratic_function.csv", true);
 
    return 0;
}
