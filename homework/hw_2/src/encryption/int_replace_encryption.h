#ifndef __hse_comp_arch_hw_intreplaceencriptionh__
#define __hse_comp_arch_hw_intreplaceencriptionh__

//------------------------------------------------------------------------------
// IntReplaceEncryption.cpp - содержит описание структуры IntReplaceEncryption
// Шифрование заменой символов на числа
//------------------------------------------------------------------------------


#include "../util/rnd.h"
#include "../util/pair.h"
#include "encrypted_text.h"

#include <iostream>
#include <fstream>

//------------------------------------------------------------------------------
class IntReplaceEncryption : public EncryptedText {
protected:
    // количество пар замены
    int pairs_count{0};
    // зашифрованный текст
    short int *encrypted_str{nullptr};
    // указатель на массив пар: 
    //          [текущий символ,
    //           целое число – подстановка при шифровании кода символа в виде короткого целого                 
    //          ]
    csPair *replace_pairs{nullptr};

    // Дешифровка строки
    void decrypt() override;

    IntReplaceEncryption() = default;

public:

    ~IntReplaceEncryption() override;

    // Ввод из потока
    static IntReplaceEncryption *buildFromStream(std::ifstream &ifst);

    // Случайный ввод
    static IntReplaceEncryption *buildRandom();

    // Вывод в поток
    void outputToStream(std::ofstream &ofst) override;
};

#endif // __hse_comp_arch_hw_intreplaceencriptionh__
