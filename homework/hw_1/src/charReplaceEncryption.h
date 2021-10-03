#ifndef __charreplaceencriptionh__
#define __charreplaceencriptionh__

//------------------------------------------------------------------------------
// cycleEncryption.h - содержит описание структуры cycleEncryption
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include <fstream>

//------------------------------------------------------------------------------
struct charReplaceEncryption {
    // длина строки
    int str_len;
    // текст
    char *encrypted_str;
};

// Ввод из потока
void In(charReplaceEncryption &cre, std::ifstream &ifst);

// Случайный ввод
void InRnd(charReplaceEncryption &cre);

// Вывод в поток
void Out(charReplaceEncryption &cre, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt(charReplaceEncryption &cre);

#endif  // __charreplaceencriptionh__
