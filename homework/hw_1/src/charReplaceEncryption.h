#ifndef __charreplaceencriptionh__
#define __charreplaceencriptionh__

//------------------------------------------------------------------------------
// charReplaceEncryption.h - содержит описание структуры charReplaceEncryption
// Шифрование заменой символов
//------------------------------------------------------------------------------

#include "pair.h"
#include <fstream>

//------------------------------------------------------------------------------
struct charReplaceEncryption {
    // длина строки
    int str_len;
    // зашифрованный текст
    char *encrypted_str;
    // колличество пар замены
    int pairs_count;
    // указатель на массив пар: [текущий символ, замещающий символ]
    ccPair *replace_pairs;
};

// Деструктор
void Clear(charReplaceEncryption &cre);

// Ввод из потока
void In(charReplaceEncryption &cre, std::ifstream &ifst);

// Случайный ввод
void InRnd(charReplaceEncryption &cre);

// Вывод в поток
void Out(charReplaceEncryption &cre, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt(charReplaceEncryption &cre);

#endif  // __charreplaceencriptionh__
