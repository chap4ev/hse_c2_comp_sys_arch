//------------------------------------------------------------------------------
// intReplaceEncryption.h - содержит описание структуры intReplaceEncryption
// Шифрование заменой символов на числа
//------------------------------------------------------------------------------

#include "intReplaceEncryption.h"


// Деструктор
void Clear(intReplaceEncryption &ire) {
    delete [] ire.encrypted_str;
    ire.str_len = 0;
    delete [] ire.replace_pairs;
    ire.pairs_count = 0;
}

// Ввод из потока
void In(intReplaceEncryption &ire, std::ifstream &ifst) {
    std::cout << "intReplaceEncryption input" << std::endl;
    ifst >> ire.str_len;
    ifst >> ire.pairs_count;

    ifst.ignore(1, ' ');
    ire.replace_pairs = new csPair[ire.pairs_count];
    for (int i = 0; i < ire.pairs_count; ++i) {
        ifst.get((ire.replace_pairs[i]).first);
    }
    for (int i = 0; i < ire.pairs_count; ++i) {
        ifst >> (ire.replace_pairs[i]).second;
    }

    ire.encrypted_str = new short int[ire.str_len];
    for (int i = 0; i < ire.str_len; ++i) {
        ifst >> ire.encrypted_str[i];
    }
}

// Случайный ввод
void InRnd(intReplaceEncryption &ire) {
    // std::cout << "random intReplaceEncryption input" << std::endl;

    ire.str_len = Random(1, 100);
    ire.pairs_count = ire.str_len;

    static auto chars = "1234567890 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static int chars_len = 63;

    ire.encrypted_str = new short int[ire.str_len];
    for (int i = 0; i < ire.str_len; ++i) {
        ire.encrypted_str[i] = (short int)(Random(-32767, 32768));
    }

    ire.replace_pairs = new csPair[ire.pairs_count];
    for (int i = 0; i < ire.pairs_count; ++i) {
        ire.replace_pairs[i].first = chars[Random(0, chars_len)];
        ire.replace_pairs[i].second = ire.encrypted_str[i];
    }
}

// Вывод в поток
void Out(intReplaceEncryption &ire, std::ofstream &ofst) {
    ofst << "[intReplaceEncryption struct:"
         << "\n\tpairs_count: " << ire.pairs_count
         << "\n\tencrypted_str: [";
    for (int i = 0; i < ire.str_len; ++i) {
        ofst << ire.encrypted_str[i] << ' ';
    }
    ofst << "] ]";
}

// Дешифровка строки
char *Decrypt(intReplaceEncryption &ire) {
    char* decrypted = new char[ire.str_len];
    for (int i = 0; i < ire.str_len; i += 1) {
        short int encrypted_c = ire.encrypted_str[i];

        for (int j = 0; j < ire.pairs_count; ++j) {
            if (encrypted_c == (ire.replace_pairs[j]).second) {
                decrypted[i] = (ire.replace_pairs[j]).first;
                break;
            }
        }
    }
    return decrypted;
}
