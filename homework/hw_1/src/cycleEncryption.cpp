//------------------------------------------------------------------------------
// cycleEncryption.cpp - содержит описание структуры
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include "cycleEncryption.h"


// Деструктор
void Clear(cycleEncryption &ce) {
    delete [] ce.encrypted_str;
    ce.str_len = 0;
}

// Ввод из потока
void In(cycleEncryption &ce, std::ifstream &ifst) {
    std::cout << "cycleEncryption input" << std::endl;

    ifst >> ce.str_len;
    ifst >> ce.shift;
    ifst.ignore(1, ' ');
    ce.encrypted_str = new char[ce.str_len];
    ifst.read(ce.encrypted_str, ce.str_len);
}

// Случайный ввод
void InRnd(cycleEncryption &ce) {
    std::cout << "random cycleEncryption input" << std::endl;

    ce.str_len = Random(1, 100);
    ce.shift = Random(-100, 101);

    auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int chars_len = 63;

    ce.encrypted_str = new char[ce.str_len];
    for (int i = 0; i < ce.str_len; ++i) {
        ce.encrypted_str[i] = (char)(
                                  ((int)chars[Random(0, chars_len)] + (CHAR_MAX + 1) + ce.shift)
                                  % (CHAR_MAX + 1)
                              );
    }
}

// Вывод в поток
void Out(cycleEncryption &ce, std::ofstream &ofst) {
    ofst << "[cycleEncryption struct: shift:" << ce.shift
         << " encrypted_str:" << ce.encrypted_str
         << ']';
}

// Дешифровка строки
char *Decrypt(cycleEncryption &ce) {
    char* decrypted = new char[ce.str_len];
    for (int i = 0; i < ce.str_len; i += 1) {
        decrypted[i] = (char)(
                           ((int)ce.encrypted_str[i] + (CHAR_MAX + 1) - ce.shift) % (CHAR_MAX + 1)
                       );
    }
    return decrypted;
}
