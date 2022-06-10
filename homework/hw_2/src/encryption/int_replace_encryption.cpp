//------------------------------------------------------------------------------
// IntReplaceEncryption.h - содержит описание структуры IntReplaceEncryption
// Шифрование заменой символов на числа
//------------------------------------------------------------------------------

#include "int_replace_encryption.h"


// Деструктор
IntReplaceEncryption::~IntReplaceEncryption() {
    delete[] encrypted_str;
    delete[] replace_pairs;
    pairs_count = 0;
}

// Ввод из потока
IntReplaceEncryption *IntReplaceEncryption::buildFromStream(std::ifstream &ifst) {
    // std::cout << "IntReplaceEncryption input" << std::endl;

    auto *ire = new IntReplaceEncryption();

    ifst >> ire->str_len;
    ifst >> ire->pairs_count;

    ifst.ignore(1, ' ');
    ire->replace_pairs = new csPair[ire->pairs_count];
    for (int i = 0; i < ire->pairs_count; ++i) {
        ifst.get((ire->replace_pairs[i]).first);
    }
    for (int i = 0; i < ire->pairs_count; ++i) {
        ifst >> (ire->replace_pairs[i]).second;
    }

    ire->encrypted_str = new short int[ire->str_len];
    for (int i = 0; i < ire->str_len; ++i) {
        ifst >> ire->encrypted_str[i];
    }

    ire->decrypt();
    return ire;
}

// Случайный ввод
IntReplaceEncryption *IntReplaceEncryption::buildRandom() {
    // std::cout << "random IntReplaceEncryption input" << std::endl;

    auto *ire = new IntReplaceEncryption();

    ire->str_len = Random(1, 100);
    ire->pairs_count = ire->str_len;

    static auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static int chars_len = 63;

    ire->encrypted_str = new short int[ire->str_len];
    for (int i = 0; i < ire->str_len; ++i) {
        ire->encrypted_str[i] = (short int) (Random(-32767, 32768));
    }

    ire->replace_pairs = new csPair[ire->pairs_count];
    for (int i = 0; i < ire->pairs_count; ++i) {
        ire->replace_pairs[i].first = chars[Random(0, chars_len)];
        ire->replace_pairs[i].second = ire->encrypted_str[i];
    }

    ire->decrypt();
    return ire;
}

// Вывод в поток
void IntReplaceEncryption::outputToStream(std::ofstream &ofst) {
    ofst << "[IntReplaceEncryption struct:"
         << "\n\tpairs_count: " << pairs_count
         << "\n\tencrypted_str: [";
    for (int i = 0; i < str_len; ++i) {
        ofst << encrypted_str[i] << ' ';
    }
    ofst << "]\n\tdecrypted_str: [" << decrypted_str << "]"
         << "\n\ttext_hash:" << hash() << "]\n";
}

// Дешифровка строки
void IntReplaceEncryption::decrypt() {
    delete[] decrypted_str;
    decrypted_str = new char[str_len];
    for (int i = 0; i < str_len; i += 1) {
        short int encrypted_c = encrypted_str[i];

        for (int j = 0; j < pairs_count; ++j) {
            if (encrypted_c == (replace_pairs[j]).second) {
                decrypted_str[i] = (replace_pairs[j]).first;
                break;
            }
        }
    }
}
