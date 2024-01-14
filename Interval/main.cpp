#include <iostream>
#include <vector>
#include <algorithm>

class Interval {
private:
    std::vector<std::pair<double, double>> intervals;
public:
    Interval(double a, double b) {
        intervals.push_back(std::make_pair(std::min(a, b), std::max(a, b)));
    }

    Interval(std::vector<std::pair<double, double>> intVec) {
        intervals = intVec;
    }

    [[nodiscard]] std::vector<std::pair<double, double>> getIntervals() const {
        return intervals;
    }

    [[nodiscard]] std::vector<double> getEndpoints() const {
        std::vector<double> endpoints;
        for (auto interval : intervals) {
            endpoints.push_back(interval.first);
            endpoints.push_back(interval.second);
        }
        return endpoints;
    }

    [[nodiscard]] double len() const {
        double totalLen = 0.0;
        for (auto interval : intervals) {
            totalLen += interval.second - interval.first;
        }
        return totalLen;
    }

    [[nodiscard]] bool in(double x) const {
        for (auto interval : intervals) {
            if (x >= interval.first && x <= interval.second) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::vector<double> split(int n) const {
        std::vector<double> splitPoints;
        std::vector<double> endpoints = getEndpoints();
        std::sort(endpoints.begin(), endpoints.end());

        double intervalLen = len();
        double step = intervalLen / n;
        double currentPoint = endpoints[0];
        splitPoints.push_back(currentPoint);

        for (int i = 1; i < endpoints.size(); i++) {
            double dist = endpoints[i] - currentPoint;
            if (dist >= step) {
                int numSteps = int(dist / step);
                double actualStep = dist / numSteps;
                for(int j = 0; j < numSteps; j++) {
                    currentPoint += actualStep;
                    splitPoints.push_back(currentPoint);
                }
            }
            currentPoint = endpoints[i];
        }

        return splitPoints;
    }

    Interval operator+(double offset) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval : intervals) {
            newIntervals.push_back(std::make_pair(interval.first + offset, interval.second + offset));
        }
        return {newIntervals};
    }

    Interval operator-(double offset) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval : intervals) {
            newIntervals.push_back(std::make_pair(interval.first - offset, interval.second - offset));
        }
        return {newIntervals};
    }

    Interval operator*(double factor) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval : intervals) {
            newIntervals.push_back(std::make_pair(interval.first * factor, interval.second * factor));
        }
        return {newIntervals};
    }

    Interval operator/(double divisor) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval : intervals) {
            newIntervals.push_back(std::make_pair(interval.first / divisor, interval.second / divisor));
        }
        return {newIntervals};
    }

    Interval operator+(const Interval& other) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval1 : intervals) {
            for (auto interval2 : other.getIntervals()) {
                double start = std::min(interval1.first, interval2.first);
                double end = std::max(interval1.second, interval2.second);
                newIntervals.push_back(std::make_pair(start, end));
            }
        }
        return {newIntervals};
    }

    Interval operator-(const Interval& other) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval1 : intervals) {
            for (auto interval2 : other.getIntervals()) {
                if (interval1.first >= interval2.second || interval1.second <= interval2.first) {
                    newIntervals.push_back(interval1);
                } else if (interval1.first < interval2.first && interval1.second <= interval2.second) {
                    newIntervals.push_back(std::make_pair(interval1.first, interval2.first));
                } else if (interval1.first >= interval2.first && interval1.second > interval2.second) {
                    newIntervals.push_back(std::make_pair(interval2.second, interval1.second));
                } else if (interval1.first < interval2.first && interval1.second > interval2.second) {
                    newIntervals.push_back(std::make_pair(interval1.first, interval2.first));
                    newIntervals.push_back(std::make_pair(interval2.second, interval1.second));
                }
            }
        }
        return {newIntervals};
    }

    Interval operator*(const Interval& other) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval1 : intervals) {
            for (auto interval2 : other.getIntervals()) {
                double start = std::max(interval1.first, interval2.first);
                double end = std::min(interval1.second, interval2.second);
                if (start <= end) {
                    newIntervals.push_back(std::make_pair(start, end));
                }
            }
        }
        return {newIntervals};
    }

    Interval operator/(const Interval& other) const {
        std::vector<std::pair<double, double>> newIntervals;
        for (auto interval1 : intervals) {
            for (auto interval2 : other.getIntervals()) {
                if (interval2.first != 0.0 && interval2.second != 0.0) {
                    double start = std::min(interval1.first / interval2.first, interval1.first / interval2.second);
                    double end = std::max(interval1.second / interval2.first, interval1.second / interval2.second);
                    newIntervals.push_back(std::make_pair(start, end));
                }
            }
        }
        return {newIntervals};
    }
};

int main() {
    Interval interval1(1.5, 3.5);
    Interval interval2({{0, 1}, {2, 3}});
    Interval interval3({{0, 1}, {2, 3}, {4, 5}, {6, 7}});

    Interval sum = interval1 + interval2;
    Interval sum2 = interval1 + 2;
    Interval diff = interval1 - interval2;
    Interval mult = interval1 * interval2;
    Interval div = interval1 / interval2;
    double len = interval2.len();
    bool in = interval2.in(1);
    std::vector<double> split = interval2.split(4);

    std::cout << "Sum interval plus interval: ";
    for (auto interval : sum.getIntervals()) {
        std::cout << "(" << interval.first << ", " << interval.second << ") ";
    }

    std::cout << "\nSum interval plus num: ";
    for (auto interval : sum2.getIntervals()) {
        std::cout << "(" << interval.first << ", " << interval.second << ") ";
    }

    std::cout << "\nDifference: ";
    for (auto interval : diff.getIntervals()) {
        std::cout << "(" << interval.first << ", " << interval.second << ") ";
    }

    std::cout << "\nIntersection: ";
    for (auto interval : mult.getIntervals()) {
        std::cout << "(" << interval.first << ", " << interval.second << ") ";
    }

    std::cout << "\nDivision: ";
    for (auto interval : div.getIntervals()) {
        std::cout << "(" << interval.first << ", " << interval.second << ") ";
    }

    std::cout << "\nSplit: ";
    for (auto value : split) {
        std::cout << value << " ";
    }

    std::cout << "\nIn: ";
    std::cout << in;

    std::cout << "\nLen: ";
    std::cout << len;

    return 0;
}
