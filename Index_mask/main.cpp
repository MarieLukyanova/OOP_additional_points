#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iterator>

template <size_t N>
class Mask {
    std::vector<bool> mask;

    void validate_mask() {
        if (mask.size() != N) {
            throw std::invalid_argument("Некорректный размер маски.");
        }
    }

public:
    template<typename ... Args>
    Mask(Args ... args) : mask{static_cast<bool>(args)...} {
        validate_mask();
    }

    size_t size() const {
        return N;
    }

    bool at(size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Индекс вне диапазона.");
        }
        return mask[index];
    }

    template <typename Container>
    void slice(Container& container) const {
        auto mask_iter = mask.cbegin();
        auto cont_iter = container.begin();
        
        while (cont_iter != container.end()) {
            if (!*mask_iter) {
                cont_iter = container.erase(cont_iter);
            } else {
                ++cont_iter;
            }
            mask_iter = std::next(mask_iter);
            if (mask_iter == mask.cend()) {
                mask_iter = mask.cbegin();
            }
        }
    }

    template <typename Container, typename TransformFunc>
    Container transform(const Container& container, TransformFunc func) const {
        Container result;
        auto mask_iter = mask.cbegin();

        std::transform(container.cbegin(), container.cend(), std::back_inserter(result),
                       [&mask_iter, &func, this](const auto& value) {
                           auto transformed_value = (mask_iter != mask.cend() && *mask_iter) ? func(value) : value;
                           mask_iter = std::next(mask_iter);
                           if (mask_iter == mask.cend()) {
                               mask_iter = mask.cbegin();
                           }
                           return transformed_value;
                       });
        return result;
    }

    template <typename Container, typename TransformFunc>
    Container slice_and_transform(Container& container, TransformFunc func) {
        slice(container);
        return transform(container, func);
    }
};


int main() {
    try {
        // Создание объекта класса Mask с размером шаблона 4
        Mask<4> maskTemplate = {1, 1, 0, 1};
        std::cout << "Размер маски: " << maskTemplate.size() << std::endl;
        std::cout << "Элемент маски с индексом 2: " << maskTemplate.at(2) << std::endl;
        std::vector<int> dataVector = {1, 2, 3, 4, 5, 6, 7};
        maskTemplate.slice(dataVector);
        std::cout << "Вектор после применения slice: ";
        for (int val : dataVector) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        std::vector<int> dataForTransform = {1, 2, 3, 4, 5, 6, 7};
        auto transformedData = maskTemplate.transform(dataForTransform, [](int x) { return x * 2; });
        std::cout << "Вектор после применения transform: ";
        for (int val : transformedData) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        Mask<3> invalidMask = {1, 0}; // Ожидается ошибка
    } catch (const std::invalid_argument& e) {
        std::cout << "Произошла ошибка при создании маски: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Произошла ошибка: индекс вне диапазона." << std::endl;
    }

    return 0;
}
