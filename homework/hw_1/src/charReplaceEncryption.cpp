//------------------------------------------------------------------------------
// charReplaceEncryption.cpp - содержит описание структуры charReplaceEncryption
// Шифрование заменой символов
//------------------------------------------------------------------------------

#include "charReplaceEncryption.h"


// Ввод из потока
void In(charReplaceEncryption &cre, std::ifstream &ifst) {
    cre.encrypted_str = new char[cre.str_len];
    ifst >> cre.pairs_count;

    cre.replace_pairs = new ccPair[cre.pairs_count];
    ifst.ignore(1, ' ');
    for (int i = 0; i < cre.pairs_count; ++i) {
        ifst.get((cre.replace_pairs[i]).first);
    }
    for (int i = 0; i < cre.pairs_count; ++i) {
        ifst.get((cre.replace_pairs[i]).second);
    }

    ifst.ignore(1, ' ');
    ifst.read(cre.encrypted_str, cre.str_len);
}

// Случайный ввод
void InRnd(charReplaceEncryption &cre) {

}

// Вывод в поток
void Out(charReplaceEncryption &cre, std::ofstream &ofst) {
    ofst << "[charReplaceEncryption struct: pairs_count: " << cre.pairs_count
         << " encrypted_str:" << cre.encrypted_str
         << ']';
}

// Дешифровка строки
char *Decrypt(charReplaceEncryption &cre) {
    char* decrypted = new char[cre.str_len];
    for (int i = 0; i < cre.str_len; i += 1) {
        char encrypted_char = cre.encrypted_str[i];

        for (int j = 0; j < cre.pairs_count; ++j) {
            if (encrypted_char == (cre.replace_pairs[j]).second){
                decrypted[i] = (cre.replace_pairs[j]).first;
                break;
            }
        }
    }
    return decrypted;
}
