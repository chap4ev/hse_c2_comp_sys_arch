//------------------------------------------------------------------------------
// intReplaceEncryption.cpp - содержит описание структуры intReplaceEncryption
// Шифрование заменой символов на числа
//------------------------------------------------------------------------------


#include "pair.h"
#include <fstream>

//------------------------------------------------------------------------------
struct intReplaceEncryption {
    // длина строки
    int str_len;
    // зашифрованный текст – целочисленный массив
    short int *encrypted_str;
    // колличество пар замены
    int pairs_count;
    // указатель на массив пар: 
    //          [текущий символ,
    //           целое число – подстановка при шифровании кода символа в виде короткого целого                 
    //          ]
    csPair *replace_pairs;
};

// Ввод из потока
void In(intReplaceEncryption &ire, std::ifstream &ifst);

// Случайный ввод
void InRnd(intReplaceEncryption &ire);

// Вывод в поток
void Out(intReplaceEncryption &ire, std::ofstream &ofst);

// Дешифровка строки
char *Decrypt(intReplaceEncryption &ire);
