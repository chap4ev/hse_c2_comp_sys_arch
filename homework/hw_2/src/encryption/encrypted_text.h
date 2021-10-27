#ifndef __hse_comp_arch_hw_encryptedtext_h__
#define __hse_comp_arch_hw_encryptedtext_h__

//------------------------------------------------------------------------------
// EncryptedText.h - содержит описание обобщающей структуры зашифрованного текста
//------------------------------------------------------------------------------

#include <iostream>
#include <cstring>

//------------------------------------------------------------------------------
// структура, обобщающая все варианты шифрования текста
class EncryptedText {
protected:
    // длина строки
    int str_len{0};
    // дешифрованный текст
    char *decrypted_str{nullptr};

    virtual void decrypt() = 0;

    EncryptedText() = default;

public:

    virtual ~EncryptedText();

    // Ввод
    static EncryptedText *buildFromStream(std::ifstream &ifdt);

    // Случайный ввод
    static EncryptedText *buildRandom();

    // Вывод
    virtual void outputToStream(std::ofstream &ofst) = 0;

    // Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
    virtual double hash();
};

#endif  // __hse_comp_arch_hw_encryptedtext_h__
