#include <iostream>
#include <vector>
#include <string>
 
class TerminalReader {
public:
    // Конструктор класса
    TerminalReader() : intContainer(nullptr), stringContainer(nullptr) {}
 
    // Метод для установки контейнера для целых чисел
    void setIntContainer(std::vector<int>& container) {
        intContainer = &container;
    }
 
    // Метод для установки контейнера для строк
    void setStringContainer(std::vector<std::string>& container) {
        stringContainer = &container;
    }
 
    // Метод для считывания очередной единицы информации
    void readNext() {
        if (intContainer == nullptr && stringContainer == nullptr) {
            throw std::logic_error("Both containers are not set.");
        }
 
        std::string input;
        std::cout << "Enter num or str: ";
        std::cin >> input;
 
        try {
            // Попробуем преобразовать в целое число
            int intValue = std::stoi(input);
            if (intContainer != nullptr) {
                intContainer->push_back(intValue);
            }
        }
        catch (std::invalid_argument&) {
            // В случае ошибки при преобразовании, считаем, что введена строка
            if (stringContainer != nullptr) {
                stringContainer->push_back(input);
            }
        }
    }
 
private:
    std::vector<int>* intContainer;
    std::vector<std::string>* stringContainer;
};
 
int main() {
    std::vector<int> int_vec;
    std::vector<std::string> str_vec;
    TerminalReader t_reader;
 
    t_reader.setIntContainer(int_vec);
    t_reader.setStringContainer(str_vec);
 
    t_reader.readNext();
    t_reader.readNext();
    t_reader.readNext();
 
    // Печать результатов
    std::cout << "Int: ";
    for (const auto& num : int_vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
 
    std::cout << "Str: ";
    for (const auto& str : str_vec) {
        std::cout << str << " ";
    }
    std::cout << std::endl;
 
    return 0;
}
