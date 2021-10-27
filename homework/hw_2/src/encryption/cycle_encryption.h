#ifndef __hse_comp_arch_hw_cycleencriptionh__
#define __hse_comp_arch_hw_cycleencriptionh__

//------------------------------------------------------------------------------
// CycleEncryption.h - содержит описание структуры CycleEncryption
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include "../util/rnd.h"
#include "encrypted_text.h"

#include <fstream>
#include <iostream>
#include <limits.h>

//------------------------------------------------------------------------------
class CycleEncryption : public EncryptedText {
protected:
    // сдвиг
    int shift{0};
    // зашифрованный текст
    char *encrypted_str{nullptr};

    // Дешифровка строки
    void decrypt() override;

public:
    CycleEncryption() = default;

    ~CycleEncryption() override;

    // Ввод из потока
    static CycleEncryption *buildFromStream(std::ifstream &ifst);

    // Случайный ввод
    static CycleEncryption *buildRandom();

    // Вывод в поток
    void outputToStream(std::ofstream &ofst) override;
};

#endif  // __hse_comp_arch_hw_cycleencriptionh__
