//------------------------------------------------------------------------------
// charReplaceEncryption.cpp - содержит описание структуры charReplaceEncryption
// Шифрование заменой символов
//------------------------------------------------------------------------------

#include "charReplaceEncryption.h"


// Деструктор
void Clear(charReplaceEncryption &cre) {
    delete [] cre.encrypted_str;
    cre.str_len = 0;
    delete [] cre.replace_pairs;
    cre.pairs_count = 0;
}

// Ввод из потока
void In(charReplaceEncryption &cre, std::ifstream &ifst) {
    std::cout << "charReplaceEncryption input" << std::endl;

    ifst >> cre.str_len;
    ifst >> cre.pairs_count;

    ifst.ignore(1, ' ');
    cre.replace_pairs = new ccPair[cre.pairs_count];
    for (int i = 0; i < cre.pairs_count; ++i) {
        ifst.get((cre.replace_pairs[i]).first);
    }
    for (int i = 0; i < cre.pairs_count; ++i) {
        ifst.get((cre.replace_pairs[i]).second);
    }

    ifst.ignore(1, ' ');
    cre.encrypted_str = new char[cre.str_len];
    ifst.read(cre.encrypted_str, cre.str_len);
}

// Случайный ввод
void InRnd(charReplaceEncryption &cre) {
    // std::cout << "random charReplaceEncryption input" << std::endl;

    cre.str_len = Random(1, 100);
    cre.pairs_count = Random(0, cre.str_len);

    static auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static int chars_len = 63;

    cre.replace_pairs = new ccPair[cre.pairs_count];
    for (int i = 0; i < cre.pairs_count; ++i) {
        cre.replace_pairs[i].first = chars[Random(0, chars_len)];
        cre.replace_pairs[i].second = chars[Random(0, chars_len)];
    }

    cre.encrypted_str = new char[cre.str_len];
    for (int i = 0; i < cre.str_len; ++i) {
        cre.encrypted_str[i] = chars[Random(0, chars_len)];
    }
}

// Вывод в поток
void Out(charReplaceEncryption &cre, std::ofstream &ofst) {
    ofst << "[charReplaceEncryption struct:"
         << "\n\tpairs_count: " << cre.pairs_count
         << "\n\tencrypted_str: [" << cre.encrypted_str << "] ]";
}

// Дешифровка строки
char *Decrypt(charReplaceEncryption &cre) {
    char* decrypted = new char[cre.str_len];
    for (int i = 0; i < cre.str_len; i += 1) {
        char encrypted_char = cre.encrypted_str[i];
        char decrypted_char = encrypted_char;
        for (int j = 0; j < cre.pairs_count; ++j) {
            if (encrypted_char == (cre.replace_pairs[j]).second) {
                decrypted_char = (cre.replace_pairs[j]).first;
                break;
            }
        }
        decrypted[i] = decrypted_char;
    }
    return decrypted;
}
