//------------------------------------------------------------------------------
// encryptedText.cpp - содержит процедуры связанные с обработкой обобщенной фигуры
// и создания произвольной фигуры
//------------------------------------------------------------------------------

#include "encryptedText.h"


// Деструктор
void Clear(encryptedText &t) {
    switch (t.e_key) {
    case language::CHARREPLACE:
        delete [] t.char_replace.encrypted_str;
        t.char_replace.str_len = 0;
        delete [] str;
        break;
    case language::CYCLE:
        delete [] t.cycle.encrypted_str;
        t.cycle.str_len = 0;
        delete [] str;
        break;
    case language::INTREPLACE:
        delete [] t.int_replace.encrypted_str;
        t.int_replace.str_len = 0;
        delete [] str;
        break;
    }
    t.str_len = 0;
}


//------------------------------------------------------------------------------
// Ввод из потока
encryptedText* In(std::ifstream &ifst) {
    encryptedText *text;
    char type[20];
    ifst >> type >> text.str_len;
    if (!strcmp(type, "charReplaceEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::CHARREPLACE;
        (text->char_replace).str_len = text.str_len;
        In(text->char_replace, ifst);
        text->str = (text->char_replace).Decrypt();

    } else if (!strcmp(type, "cycleEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::CYCLE;
        (text->cycle).str_len = text.str_len;
        In(text->cycle, ifst);
        text->str = (text->cycle).Decrypt();

    } else if (!strcmp(type, "intReplaceEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::INTREPLACE;
        (text->int_replace).str_len = text.str_len;
        In(text->int_replace, ifst);
        text->str = (text->int_replace).Decrypt();

    } else {
        std::cout << "ERROR: Wrong type " << type;
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
        InRnd(text->p);
    } else if (type == 2) {
        text = new encryptedText;
        text->e_key = encryptedText::CYCLE;
        InRnd(text->f);
    } else {
        text = new encryptedText;
        text->e_key = encryptedText::INTREPLACE;
        InRnd(text->o);
    }
    return text;
}

//------------------------------------------------------------------------------
// Вывод в поток
void Out(encryptedText &t, std::ofstream &ofst) {
    switch (t.e_key) {
    case language::CHARREPLACE:
        Out(t.char_replace, ofst);
        break;
    case language::CYCLE:
        Out(t.cycle, ofst);
        break;
    case language::INTREPLACE:
        Out(t.int_replace, ofst);
        break;
    }
}

//------------------------------------------------------------------------------
// Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
double TextHash(encryptedText &t) {
    double sum = 0;
    for (int i = 0; i < t.str_len; i += 1) {
        sum += (double)str[i];
    }
    return sum / str_len;
}
