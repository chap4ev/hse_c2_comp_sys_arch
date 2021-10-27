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
    // количество пар замены
    int pairs_count{0};
    // зашифрованный текст
    char *encrypted_str{nullptr};
    // указатель на массив пар: [текущий символ, замещающий символ]
    ccPair *replace_pairs{nullptr};

    // Дешифровка строки
    void decrypt() override;

    CharReplaceEncryption() = default;

public:

    ~CharReplaceEncryption() override;

    // Ввод из потока
    static CharReplaceEncryption *buildFromStream(std::ifstream &ifst);

    // Случайный ввод
    static CharReplaceEncryption *buildRandom();

    // Вывод в поток
    void outputToStream(std::ofstream &ofst) override;
};

#endif  // __hse_comp_arch_hw_charreplaceencriptionh__
