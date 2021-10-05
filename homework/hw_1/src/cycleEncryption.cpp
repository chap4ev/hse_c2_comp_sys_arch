//------------------------------------------------------------------------------
// cycleEncryption.cpp - содержит описание структуры
// Шифрование циклическим сдвигом кода каждого символа на n
//------------------------------------------------------------------------------

#include "cycleEncryption.h"

// Ввод из потока
void In(cycleEncryption &ce, std::ifstream &ifst) {
    ce.encrypted_str = new char[ce.str_len];
    ifst >> ce.shift;
    ifst.ignore(1, ' ');
    ifst.read(ce.encrypted_str, ce.str_len);
}

// Случайный ввод
void InRnd(cycleEncryption &ce) {

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
        decrypted[i] = (char)(((int)ce.encrypted_str[i] - ce.shift) % (CHAR_MAX + 1));
    }
    return decrypted;
}
