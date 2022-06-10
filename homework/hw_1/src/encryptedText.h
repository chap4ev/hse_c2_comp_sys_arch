#ifndef __encryptedtext__
#define __encryptedtext__

//------------------------------------------------------------------------------
// encryptedText.h - содержит описание обобщающей структуры зашифрованного текста 
//------------------------------------------------------------------------------

#include <iostream>
#include <cstring>

#include "charReplaceEncryption.h"
#include "cycleEncryption.h"
#include "intReplaceEncryption.h"
#include "rnd.h"

//------------------------------------------------------------------------------
// структура, обобщающая все варианты шифрования текста
struct encryptedText {
    // длина строки
    int str_len;
    // текст
    char *str;

    // значения ключей для каждого из видов шифрования
    enum encryptionKey {CHARREPLACE, CYCLE, INTREPLACE};
    encryptionKey e_key;

    // используемые альтернативы
    union {
        charReplaceEncryption char_replace;
        cycleEncryption cycle;
        intReplaceEncryption int_replace;
    };
};

// Деструктор
void Clear(encryptedText &t);

// Ввод
encryptedText *In(std::ifstream &ifdt);

// Случайный ввод
encryptedText *InRnd();

// Вывод
void Out(encryptedText &t, std::ofstream &ofst);

// Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
double TextHash(encryptedText &t);

#endif  // __encryptedtext__
