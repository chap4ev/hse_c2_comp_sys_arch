#ifndef __hse_comp_arch_hw_container_h__
#define __hse_comp_arch_hw_container_h__

#include <fstream>
#include "../encryption/encrypted_text.h"


// Максимальная длина
const size_t CONTAINER_MAX_SIZE = 10000;

// Простейший контейнер на основе одномерного массива
class Container {
private:
    int size{0};

    EncryptedText **data{new EncryptedText *[CONTAINER_MAX_SIZE]};

public:
    Container() = default;
    ~Container();

    // Ввод содержимого контейнера из указанного потока
    void inputFromStream(std::ifstream &ifst);

    // Случайный ввод содержимого контейнера
    void randomFill(int size);

    // Вывод содержимого контейнера в указанный поток
    void outputToStream(std::ofstream &ofst);

    // Сортировка по возрастанию с помощью прямого выбора (Straight Selection)
    void sort();
};

#endif  // __hse_comp_arch_hw_container_h__
