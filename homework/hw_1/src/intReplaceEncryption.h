#ifndef __intreplaceencriptionh__
#define __intreplaceencriptionh__

//------------------------------------------------------------------------------
// cycleEncryption.h - содержит описание структуры cycleEncryption
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include <fstream>

//------------------------------------------------------------------------------
struct intReplaceEncryption {
    // длина строки
    int str_len;
    // текст
    char *encrypted_str;
};

// Ввод из потока
void In(intReplaceEncryption &ire, std::ifstream &ifst);

// Случайный ввод
void InRnd(intReplaceEncryption &ire);

// Вывод в поток
void Out(intReplaceEncryption &ire, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt(intReplaceEncryption &ire);

#endif  // __charreplaceencriptionh__
