//------------------------------------------------------------------------------
// container_Constr.cpp - содержит функции обработки контейнера
//------------------------------------------------------------------------------

#include "container.h"

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
Container::~Container() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    size = 0;
}

//------------------------------------------------------------------------------
// Ввод содержимого контейнера из указанного потока
void Container::inputFromStream(std::ifstream &ifst) {
    while (!ifst.eof()) {
        if ((data[size] = EncryptedText::inputFromStream(ifst)) != nullptr) {
            size++;
        }
    }
}

// Случайный ввод содержимого контейнера
void Container::randomFill(int newSize) {
    while (size < newSize) {
        if ((data[size] = EncryptedText::randomFill()) != nullptr) {
            size++;
        }
    }
}

// Вывод содержимого контейнера в указанный поток
void Container::outputToStream(std::ofstream &ofst) {
    ofst << "Container contains " << size << " elements." << std::endl;
    for (int i = 0; i < size; ++i) {
        ofst << i << ": ";
        data[i]->outputToStream(ofst);
    }
}

//------------------------------------------------------------------------------
// Сортировка по возрастанию с помощью прямого выбора (Straight Selection)
void Container::sort() {
    int j, min_i;
    double min_hash, j_hash;
    for (int i = 0; i < size; ++i) {
        min_i = i;
        min_hash = data[min_i]->hash();
        for (j = i + 1; j < size; ++j) {
            j_hash = data[j]->hash();
            if (j_hash < min_hash) {
                min_i = j;
                min_hash = j_hash;
            }
        }
        EncryptedText *tmp = data[i];
        data[i] = data[min_i];
        data[min_i] = tmp;
    }
}
