#include <vector>
#include <algorithm>
#include <iostream>
 
template <typename T>
class ToSortContainer {
    std::vector<T> data_;
 
public:
    ToSortContainer(std::initializer_list<T> values)
        : data_(values)
    {}
 
    template <typename Comparator>
    std::vector<T> getSortedBy(Comparator cmp) const {
        auto sorted = data_;
        std::sort(sorted.begin(), sorted.end(), cmp);
        return sorted;
    }
};
 
int main() {
    ToSortContainer<int> tsc = { 2, 3, -4, 1, 6 };
 
    auto x = tsc.getSortedBy(std::greater<int>());
    auto y = tsc.getSortedBy([](auto x, auto y) { return x < y; });
 
    // Printing the sorted values
    std::cout << "Sorted in descending order: ";
    for (auto val : x) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
 
    std::cout << "Sorted in ascending order: ";
    for (auto val : y) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
 
    return 0;
}
