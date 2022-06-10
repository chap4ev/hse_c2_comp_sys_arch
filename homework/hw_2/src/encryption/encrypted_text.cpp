//------------------------------------------------------------------------------
// EncryptedTexcpp - содержит процедуры связанные с созданием удалением и
// обработкой EncryptedText
//------------------------------------------------------------------------------

#include "encrypted_text.h"

#include "char_replace_encryption.h"
#include "cycle_encryption.h"
#include "int_replace_encryption.h"

// Деструктор
EncryptedText::~EncryptedText() {
    delete[] decrypted_str;
    str_len = 0;
}


//------------------------------------------------------------------------------
// Ввод из потока
EncryptedText *EncryptedText::buildFromStream(std::ifstream &ifdt) {
    EncryptedText *text;
    char type[50];
    ifdt >> type;
    if (!strcmp(type, "CharReplaceEncryption")) {
        text = dynamic_cast<EncryptedText *>(CharReplaceEncryption::buildFromStream(ifdt));
        ifdt.ignore(1000, '\n');
    } else if (!strcmp(type, "CycleEncryption")) {
        text = dynamic_cast<EncryptedText *>(CycleEncryption::buildFromStream(ifdt));
        ifdt.ignore(1000, '\n');
    } else if (!strcmp(type, "IntReplaceEncryption")) {
        text = dynamic_cast<EncryptedText *>(IntReplaceEncryption::buildFromStream(ifdt));
        ifdt.ignore(1000, '\n');

    } else {
        std::cout << "ERROR: Wrong type [" << type << "]\n";
        delete text;
        exit(1);
    }
    return text;
}

// Случайный ввод
EncryptedText *EncryptedText::buildRandom() {
    EncryptedText *text;
    auto type = Random(0, 3);

    if (type == 0) {
        text = dynamic_cast<EncryptedText *>(CharReplaceEncryption::buildRandom());
    } else if (type == 1) {
        text = dynamic_cast<EncryptedText *>(CycleEncryption::buildRandom());
    } else if (type == 2) {
        text = dynamic_cast<EncryptedText *>(IntReplaceEncryption::buildRandom());
    }

    return text;
}

//------------------------------------------------------------------------------
// Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
double EncryptedText::hash() {
    double sum = 0;
    for (int i = 0; i < str_len; i += 1) {
        sum += (double) decrypted_str[i];
    }
    return sum / str_len;
}
