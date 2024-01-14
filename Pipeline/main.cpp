#include <algorithm>
#include <vector>
#include <utility>
 
template<typename T>
class ToSortContainer {
    std::vector<T> info;
 
public:
    explicit ToSortContainer(std::vector<T> data)
            : info(std::move(data)) {}
 
    ToSortContainer(std::initializer_list<T> data)
            : ToSortContainer(std::vector<T>{data}) {}
 
    template<typename Comparator>
    std::vector<T> getSortedBy(Comparator cmp) {
        std::sort(info.begin(), info.end(), cmp);
        return info;
    }
};
 
int main() {
    ToSortContainer<int> tsc = {2, 3, -4, 1, 6};
    auto x = tsc.getSortedBy(std::greater<int>{});
    auto y = tsc.getSortedBy([](auto x, auto y) { return x < y; });
    return 0;
}
