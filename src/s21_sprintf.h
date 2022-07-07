#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_
#include <stdarg.h>
#include "s21_string.h"
// Спецификаторы: c, d, i, f, s, u, %
    // c - Символ,
    // d - Знаковое десятичное целое число,
    // i - Знаковое десятичное целое число,
    // f - Десятичное число с плавающей точкой,
    // s - Строка символов,
    // u - Беззнаковое десятичное целое число,
    // % - Символ %;
// Флаги: -, +, (пробел)
    // -
    // Выравнивание по левому краю в пределах заданной ширины поля;
    // Выравнивание по правому краю используется по умолчанию (см. подспецификатор ширины).

    // +
    // Заставляет явно указывать знак плюс или минус (+ или -) даже для положительных чисел.
    // По умолчанию только отрицательным числам предшествует знак "-".

    // (пробел)
    // Если знак не будет выведен, перед значением вставляется пробел.
// Ширина: (число)
    // (число)
    // Минимальное количество печатаемых символов.
    // Если выводимое значение короче этого числа, результат дополняется пробелами.
    // Значение не усекается, даже если результат больше.
// Точность: .(число)

// Длина: h, l
    // h
    // Аргумент интерпретируется как короткое int или короткое int без знака
    //  (применяется только к целочисленным спецификаторам: i, d, o, u, x и X).

    // l
    // Аргумент интерпретируется как длинное int или длинное int без знака
    // для целочисленных спецификаторов (i, d, o, u, x и X) и как широкий символ
    // или строка широких символов для спецификаторов c и s.

// %[флаги][ширина][.точность][длина]спецификатор
enum specificator {
    unknown_spec,
    d_spec,
    i_spec,
    f_spec,
    c_spec,
    s_spec,
    u_spec,
    percent_spec
};

enum length {
    unknown_len,
    h_len,
    l_len
};

struct format {
    // флаги
    int plus;
    int minus;
    int space;
    // ширина
    int width;
    // точность
    int precision;
    // длина
    enum length length;
    // спецификатор
    enum specificator spec;
};

int extract_flags(const char* format, struct format *f);
int extract_width(const char* format, struct format *f);
int extract_precision(const char* format, struct format *f);
int extract_length(const char* format, struct format *f);
int extract_spec(const char* format, struct format *f);
int s21_sprintf(char *str, const char *format, ...);
char* spec_string(struct format f, va_list* args);
char* spec_d(struct format f, va_list* args);
char* spec_u(struct format f, va_list* args);
char* spec_s(struct format f, va_list* args);
char* spec_c(va_list* args);
char* spec_f(struct format f, va_list* args);
int s21_atoi(const char* str, int n);
char* s21_itoa(long int c);
char* s21_itoa_unsigned(unsigned long int c);
char* adjusted_width(struct format f, const char* str);
char* adjusted_precision_for_int(struct format f, const char* str);
char* adjusted_precision_for_string(struct format f, const char* str);


#endif  // SRC_S21_SPRINTF_H_
