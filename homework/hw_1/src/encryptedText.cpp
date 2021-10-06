//------------------------------------------------------------------------------
// encryptedText.cpp - содержит процедуры связанные с созданием удалением и
// обработкой encryptedText
//------------------------------------------------------------------------------

#include "encryptedText.h"


// Деструктор
void Clear(encryptedText &t) {
    switch (t.e_key) {
    case encryptedText::CHARREPLACE:
        Clear(t.char_replace);
        break;
    case encryptedText::CYCLE:
        Clear(t.cycle);
        break;
    case encryptedText::INTREPLACE:
        Clear(t.int_replace);
        break;
    }
    delete [] t.str;
    t.str_len = 0;
}


//------------------------------------------------------------------------------
// Ввод из потока
encryptedText* In(std::ifstream &ifst) {
    encryptedText *text = new encryptedText();
    char type[50];
    ifst >> type;
    if (!strcmp(type, "charReplaceEncryption")) {
        text->e_key = encryptedText::CHARREPLACE;
        In(text->char_replace, ifst);
        ifst.ignore(1000, '\n');
        text->str_len = (text->char_replace).str_len;
        text->str = Decrypt(text->char_replace);

    } else if (!strcmp(type, "cycleEncryption")) {
        text->e_key = encryptedText::CYCLE;
        In(text->cycle, ifst);
        ifst.ignore(1000, '\n');
        text->str_len = (text->cycle).str_len;
        text->str = Decrypt(text->cycle);

    } else if (!strcmp(type, "intReplaceEncryption")) {
        text->e_key = encryptedText::INTREPLACE;
        In(text->int_replace, ifst);
        ifst.ignore(1000, '\n');
        text->str_len = (text->int_replace).str_len;
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
    encryptedText *text = new encryptedText();
    auto type = Random(0, 2);

    if (type == 0) {
        text->e_key = encryptedText::CHARREPLACE;
        InRnd(text->char_replace);
        text->str_len = (text->char_replace).str_len;
        text->str = Decrypt(text->char_replace);

    } else if (type == 1) {
        text->e_key = encryptedText::CYCLE;
        InRnd(text->cycle);
        text->str_len = (text->cycle).str_len;
        text->str = Decrypt(text->cycle);

    } else if (type == 2) {
        text->e_key = encryptedText::INTREPLACE;
        InRnd(text->int_replace);
        text->str_len = (text->int_replace).str_len;
        text->str = Decrypt(text->int_replace);
    }

    return text;
}

//------------------------------------------------------------------------------
// Вывод в поток
void Out(encryptedText &t, std::ofstream &ofst) {
    ofst << "[encryptedText struct:";
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
    ofst << "\ndecrypted str: [" << t.str << "]"
         << "\ntext_hash:" << TextHash(t) << "]\n";
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
