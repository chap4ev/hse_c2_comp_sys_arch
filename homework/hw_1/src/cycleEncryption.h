#ifndef __cycleencriptionh__
#define __cycleencriptionh__

//------------------------------------------------------------------------------
// cycleEncryption.h - содержит описание структуры cycleEncryption
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include "rnd.h"
#include <fstream>
#include <iostream>
#include <limits.h>

//------------------------------------------------------------------------------
struct cycleEncryption {
    // длина строки
    int str_len;
    // зашифрованный текст
    char *encrypted_str;
    // сдвиг
    int shift;
};


// Деструктор
void Clear(cycleEncryption &ce);

// Ввод из потока
void In(cycleEncryption &ce, std::ifstream &ifst);

// Случайный ввод
void InRnd(cycleEncryption &ce);

// Вывод в поток
void Out(cycleEncryption &ce, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt(cycleEncryption &ce);

#endif  // __cycleencriptionh__
