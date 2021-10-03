//------------------------------------------------------------------------------
// encryptedText.cpp - содержит процедуры связанные с обработкой обобщенной фигуры
// и создания произвольной фигуры
//------------------------------------------------------------------------------

#include "encryptedText.h"

// Ввод
encryptedText *In(std::ifstream &ifdt);

// Случайный ввод
encryptedText *InRnd();

// Вывод
void Out(encryptedText &t, std::ofstream &ofst);

// Частное от деления суммы кодов незашифрованной строки на число символов в этой строке
double TextHash(encryptedText &t);

//------------------------------------------------------------------------------
// Ввод из потока
encryptedText* In(std::ifstream &ifst) {
    encryptedText *text;
    char type[20];
    int length;
    ifst >> type >> text.str_len;
    if (!strcmp(type, "charReplaceEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::CHARREPLACE;
        In(text->charReplace, ifst);
    } else if (!strcmp(type, "cycleEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::CYCLE;
        In(text->cycle, ifst);
    } else if (!strcmp(type, "intReplaceEncryption")) {
        text = new encryptedText;
        text->e_key = encryptedText::INTREPLACE;
        In(text->intReplace, ifst);
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
        text->k = encryptedText::CHARREPLACE;
        InRnd(text->p);
    } else if (type == 2) {
        text = new encryptedText;
        text->k = encryptedText::CYCLE;
        InRnd(text->f);
    } else {
        text = new encryptedText;
        text->k = encryptedText::INTREPLACE;
        InRnd(text->o);
    }
    return text;
}

//------------------------------------------------------------------------------
// Вывод параметров текущего ЯП в поток
void Out(language &lang, std::ofstream &ofst) {
    switch (lang.k) {
        case language::PROCEDURE:
            Out(lang.p, ofst);
            break;
        case language::FUNCTIONAL:
            Out(lang.f, ofst);
            break;
        case language::OOP:
            Out(lang.o, ofst);
            break;
        default:
            ofst << "Incorrect language type!\n";
    }
}

//------------------------------------------------------------------------------
// Вычисление частного от деления года создания на количество
// символов в названии (действительное число)
double YearDividedByNameLength(language &lang) {
    switch (lang.k) {
        case language::PROCEDURE:
            return YearDividedByNameLength(lang.p);
        case language::FUNCTIONAL:
            return YearDividedByNameLength(lang.f);
        case language::OOP:
            return YearDividedByNameLength(lang.o);
        default:
            return 0;
    }
}
