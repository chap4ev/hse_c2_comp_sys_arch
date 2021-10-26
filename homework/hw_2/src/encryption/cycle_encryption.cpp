//------------------------------------------------------------------------------
// CycleEncryption.cpp - содержит описание структуры
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include "cycle_encryption.h"

// Деструктор
CycleEncryption::~CycleEncryption() {
    delete[] encrypted_str;
}

// Ввод из потока
CycleEncryption *CycleEncryption::inputFromStream(std::ifstream &ifst) {
    // std::cout << "CycleEncryption input" << std::endl;

    auto *ce = new CycleEncryption();

    ifst >> ce->str_len;
    ifst >> ce->shift;
    ifst.ignore(1, ' ');
    ce->encrypted_str = new char[ce->str_len];
    ifst.read(ce->encrypted_str, ce->str_len);

    ce->decrypt();
    return ce;
}

// Случайный ввод
CycleEncryption *CycleEncryption::randomFill() {
    // std::cout << "random CycleEncryption input" << std::endl;

    auto *ce = new CycleEncryption();

    ce->str_len = Random(1, 100);
    ce->shift = Random(-100, 101);

    static auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static int chars_len = 63;

    ce->encrypted_str = new char[ce->str_len];
    for (int i = 0; i < ce->str_len; ++i) {
        ce->encrypted_str[i] = (char) (
                ((int) chars[Random(0, chars_len)] + (CHAR_MAX + 1) + ce->shift)
                % (CHAR_MAX + 1)
        );
    }

    ce->decrypt();
    return ce;
}

// Вывод в поток
void CycleEncryption::outputToStream(std::ofstream &ofst) {
    ofst << "[CycleEncryption struct: "
         << "\n\tshift: " << shift
         << "\n\tencrypted_str: [" << encrypted_str << "]"
         << "\n\tdecrypted_str: [" << decrypted_str << "]"
         << "\n\ttext_hash:" << hash() << "]\n";
}

// Дешифровка строки
void CycleEncryption::decrypt() {
    delete[] decrypted_str;
    decrypted_str = new char[str_len];
    for (int i = 0; i < str_len; i += 1) {
        decrypted_str[i] = (char) (
                ((int) encrypted_str[i] + (CHAR_MAX + 1) - shift) % (CHAR_MAX + 1)
        );
    }
}
