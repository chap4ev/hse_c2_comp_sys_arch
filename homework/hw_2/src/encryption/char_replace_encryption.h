#ifndef __hse_comp_arch_hw_charreplaceencriptionh__
#define __hse_comp_arch_hw_charreplaceencriptionh__

//------------------------------------------------------------------------------
// CharReplaceEncryption.h - содержит описание структуры CharReplaceEncryption
// Шифрование заменой символов
//------------------------------------------------------------------------------

#include "../util/pair.h"
#include "../util/rnd.h"
#include "encrypted_text.h"

#include <iostream>
#include <fstream>

//------------------------------------------------------------------------------
class CharReplaceEncryption : public EncryptedText {
protected:
    // зашифрованный текст
    char *encrypted_str{nullptr};
    // количество пар замены
    int pairs_count{0};
    // указатель на массив пар: [текущий символ, замещающий символ]
    ccPair *replace_pairs{nullptr};

    // Дешифровка строки
    void decrypt() override;

public:
    CharReplaceEncryption() = default;

    ~CharReplaceEncryption() override;

    // Ввод из потока
    static CharReplaceEncryption *inputFromStream(std::ifstream &ifst);

    // Случайный ввод
    static CharReplaceEncryption *randomFill();

    // Вывод в поток
    void outputToStream(std::ofstream &ofst) override;
};

#endif  // __hse_comp_arch_hw_charreplaceencriptionh__
