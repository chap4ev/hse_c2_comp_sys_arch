//------------------------------------------------------------------------------
// CharReplaceEncryption.cpp - содержит описание структуры CharReplaceEncryption
// Шифрование заменой символов
//------------------------------------------------------------------------------

#include "char_replace_encryption.h"

// Деструктор
CharReplaceEncryption::~CharReplaceEncryption() {
    delete[] encrypted_str;
    delete[] replace_pairs;
    pairs_count = 0;
}

// Ввод из потока
CharReplaceEncryption *CharReplaceEncryption::inputFromStream(std::ifstream &ifst) {
    // std::cout << "CharReplaceEncryption input" << std::endl;

    auto *cre = new CharReplaceEncryption();

    ifst >> cre->str_len;
    ifst >> cre->pairs_count;

    ifst.ignore(1, ' ');
    cre->replace_pairs = new ccPair[cre->pairs_count];
    for (int i = 0; i < cre->pairs_count; ++i) {
        ifst.get((cre->replace_pairs[i]).first);
    }
    for (int i = 0; i < cre->pairs_count; ++i) {
        ifst.get((cre->replace_pairs[i]).second);
    }

    ifst.ignore(1, ' ');
    cre->encrypted_str = new char[cre->str_len];
    ifst.read(cre->encrypted_str, cre->str_len);

    cre->decrypt();
    return cre;
}

// Случайный ввод
CharReplaceEncryption *CharReplaceEncryption::randomFill() {
    // std::cout << "random CharReplaceEncryption input" << std::endl;

    auto *cre = new CharReplaceEncryption();

    cre->str_len = Random(1, 100);
    cre->pairs_count = Random(0, cre->str_len);

    static auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static int chars_len = 63;

    cre->replace_pairs = new ccPair[cre->pairs_count];
    for (int i = 0; i < cre->pairs_count; ++i) {
        cre->replace_pairs[i].first = chars[Random(0, chars_len)];
        cre->replace_pairs[i].second = chars[Random(0, chars_len)];
    }

    cre->encrypted_str = new char[cre->str_len];
    for (int i = 0; i < cre->str_len; ++i) {
        cre->encrypted_str[i] = chars[Random(0, chars_len)];
    }
    cre->decrypt();
    return cre;
}

// Вывод в поток
void CharReplaceEncryption::outputToStream(std::ofstream &ofst) {
    ofst << "[CharReplaceEncryption struct:"
         << "\n\tpairs_count: " << pairs_count
         << "\n\tencrypted_str: [" << encrypted_str << "]"
         << "\n\tdecrypted_str: [" << decrypted_str << "]"
         << "\n\ttext_hash:" << hash() << "]\n";
}

// Дешифровка строки
void CharReplaceEncryption::decrypt() {
    delete[] decrypted_str;
    decrypted_str = new char[str_len];
    for (int i = 0; i < str_len; i += 1) {
        char encrypted_char = encrypted_str[i];
        char decrypted_char = encrypted_char;
        for (int j = 0; j < pairs_count; ++j) {
            if (encrypted_char == (replace_pairs[j]).second) {
                decrypted_char = (replace_pairs[j]).first;
                break;
            }
        }
        decrypted_str[i] = decrypted_char;
    }
}
