//------------------------------------------------------------------------------
// main.cpp - содержит главную функцию,
// обеспечивающую простое тестирование
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>   // для функции time()
#include <cstring>

#include "container/container.h"

void errMessage1() {
    std::cout << "incorrect command line!\n"
                 "  Waited:\n"
                 "     command -f infile outfile01 outfile02\n"
                 "  Or:\n"
                 "     command -n number outfile01 outfile02\n";
}

void errMessage2() {
    std::cout << "incorrect qualifier value!\n"
                 "  Waited:\n"
                 "     command -f infile outfile01 outfile02\n"
                 "  Or:\n"
                 "     command -n number outfile01 outfile02\n";
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    if (argc != 5) {
        errMessage1();
        return 1;
    }

    std::cout << "Start" << std::endl;
    auto *container = new Container;

    // cout << "argv[1] = " << argv[1] << "\n";
    if (!strcmp(argv[1], "-f")) {
        std::ifstream ifst(argv[2]);
        std::cout << "Container filling" << std::endl;
        container->inputFromStream(ifst);
        std::cout << "Container filled" << std::endl;
    } else if (!strcmp(argv[1], "-n")) {
        auto size = atoi(argv[2]);
        if ((size < 1) || (size > 1000)) {
            std::cout << "incorrect numer = "
                      << size
                      << ". Set 0 < number <= 10000\n";
            return 3;
        }
        // системные часы в качестве инициализатора
        srand(static_cast<unsigned int>(time(nullptr)));
        // Заполнение контейнера генератором случайных чисел
        std::cout << "Container random filling" << std::endl;
        container->randomFill(size);
        std::cout << "Container filled" << std::endl;
    } else {
        errMessage2();
        return 2;
    }

    // Вывод содержимого контейнера в файл
    std::ofstream ofst1(argv[3]);
    ofst1 << "Filled Container:\n";
    container->outputToStream(ofst1);

    // Сортировка по возрастанию и вывод в ofst2
    std::ofstream ofst2(argv[4]);
    container->sort();
    ofst2 << "Sorted Container:\n";
    container->outputToStream(ofst2);

    std::cout << "Stop" << std::endl;
    return 0;
}
