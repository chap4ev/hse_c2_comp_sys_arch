//------------------------------------------------------------------------------
// encryptedText.cpp - содержит процедуры связанные с созданием удалением и
// обработкой encryptedText
//------------------------------------------------------------------------------

#include "encryptedText.h"


// Деструктор
void Clear(encryptedText &t) {
    switch (t.e_key) {
    case encryptedText::CHARREPLACE:
        delete [] t.char_replace.encrypted_str;
        t.char_replace.str_len = 0;
        delete [] t.char_replace.replace_pairs;
        t.char_replace.pairs_count = 0;
        delete [] t.str;
        break;
    case encryptedText::CYCLE:
        delete [] t.cycle.encrypted_str;
        t.cycle.str_len = 0;
        delete [] t.str;
        break;
    case encryptedText::INTREPLACE:
        delete [] t.int_replace.encrypted_str;
        t.int_replace.str_len = 0;
        delete [] t.int_replace.replace_pairs;
        t.int_replace.pairs_count = 0;
        delete [] t.str;
        break;
    }
    t.str_len = 0;
}


//------------------------------------------------------------------------------
// Ввод из потока
encryptedText* In(std::ifstream &ifst) {
    encryptedText *text = new encryptedText();
    char type[50];
    ifst >> type >> text->str_len;
    if (!strcmp(type, "charReplaceEncryption")) {
        std::cout << "charReplaceEncryption input" << std::endl; 
        text->e_key = encryptedText::CHARREPLACE;
        (text->char_replace).str_len = text->str_len;
        In(text->char_replace, ifst);
        text->str = Decrypt(text->char_replace);

    } else if (!strcmp(type, "cycleEncryption")) {
        std::cout << "cycleEncryption input" << std::endl; 
        text->e_key = encryptedText::CYCLE;
        (text->cycle).str_len = text->str_len;
        In(text->cycle, ifst);
        text->str = Decrypt(text->cycle);

    } else if (!strcmp(type, "intReplaceEncryption")) {
        std::cout << "intReplaceEncryption input" << std::endl; 
        text->e_key = encryptedText::INTREPLACE;
        (text->int_replace).str_len = text->str_len;
        In(text->int_replace, ifst);
        text->str = Decrypt(text->int_replace);

    } else {
        std::cout << "ERROR: Wrong type [" << type << "]\n";
        delete text;
        exit(1);
    }
    return text;
}

// Случайный ввод
encryptedText *InRnd() {
    encryptedText *text;
    auto type = rand() % 3;
    if (type == 0) {
        text = new encryptedText;
        text->e_key = encryptedText::CHARREPLACE;
        InRnd(text->char_replace);
    } else if (type == 2) {
        text = new encryptedText;
        text->e_key = encryptedText::CYCLE;
        InRnd(text->cycle);
    } else {
        text = new encryptedText;
        text->e_key = encryptedText::INTREPLACE;
        InRnd(text->int_replace);
    }
    return text;
}

//------------------------------------------------------------------------------
// Вывод в поток
void Out(encryptedText &t, std::ofstream &ofst) {
    ofst << "[encryptedText struct:\n";
    switch (t.e_key) {
        case encryptedText::CHARREPLACE:
            Out(t.char_replace, ofst);
            break;
        case encryptedText::CYCLE:
            Out(t.cycle, ofst);
            break;
        case encryptedText::INTREPLACE:
            Out(t.int_replace, ofst);
            break;
    }
    ofst << "\ndecrypted str:" << t.str << "]\n";
}

//------------------------------------------------------------------------------
// Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
double TextHash(encryptedText &t) {
    double sum = 0;
    for (int i = 0; i < t.str_len; i += 1) {
        sum += (double)t.str[i];
    }
    return sum / t.str_len;
}
