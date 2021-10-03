#ifndef __cycleencriptionh__
#define __cycleencriptionh__

//------------------------------------------------------------------------------
// cycleEncryption.h - содержит описание структуры cycleEncryption
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include <fstream>
#include <limits.h>

//------------------------------------------------------------------------------
struct cycleEncryption {
    // сдвиг
    int shift;
    // длина строки
    int str_len;
    // текст
    char *encrypted_str;
};

// Ввод из потока
void In(cycleEncryption &ce, std::ifstream &ifst);

// Случайный ввод
void InRnd(cycleEncryption &ce);

// Вывод в поток
void Out(cycleEncryption &ce, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt();

#endif  // __cycleencriptionh__
