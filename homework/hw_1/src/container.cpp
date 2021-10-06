//------------------------------------------------------------------------------
// container_Constr.cpp - содержит функции обработки контейнера
//------------------------------------------------------------------------------

#include "container.h"

//------------------------------------------------------------------------------
// Инициализация контейнера
void Init(container &c) {
    c.len = 0;
}

//------------------------------------------------------------------------------
// Очистка контейнера от элементов (освобождение памяти)
void Clear(container &c) {
    for (int i = 0; i < c.len; i++) {
        Clear(*(c.cont[i]));
        delete c.cont[i];
    }
    c.len = 0;
}

//------------------------------------------------------------------------------
// Ввод содержимого контейнера из указанного потока
void In(container &c, std::ifstream &ifst) {
    while (!ifst.eof()) {
        if ((c.cont[c.len] = In(ifst)) != 0) {
            c.len++;
        }
    }
}

// Случайный ввод содержимого контейнера
void InRnd(container &c, int size) {
    while (c.len < size) {
        if ((c.cont[c.len] = InRnd()) != nullptr) {
            c.len++;
        }
    }
}

// Вывод содержимого контейнера в указанный поток
void Out(container &c, std::ofstream &ofst) {
    ofst << "Container contains " << c.len << " elements." << std::endl;
    for (int i = 0; i < c.len; i++) {
        ofst << i << ": ";
        Out(*(c.cont[i]), ofst);
    }
}

//------------------------------------------------------------------------------
// Сортировка по возрастанию с помощью прямого выбора (Straight Selection)
void Sort(container &c) {
    int j, min_i;
    double min_hash, j_hash;
    for (int i = 0; i < c.len; ++i) {
        min_i = i;
        min_hash = TextHash(*c.cont[min_i]);
        for (j = i + 1; j < c.len; ++j) {
            j_hash = TextHash(*c.cont[j]);
            if (j_hash < min_hash) {
                min_i = j;
                min_hash = j_hash;
            }
        }
        encryptedText *tmp = c.cont[i];
        c.cont[i] = c.cont[min_i];
        c.cont[min_i] = tmp;
    }
}
