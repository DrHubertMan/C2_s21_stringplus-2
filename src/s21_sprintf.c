#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
    str[0] = '\0';  //  для корректной работы strcat
    va_list args;
    va_start(args, format);
    s21_size_t format_length = s21_strlen(format);
    for (s21_size_t i = 0; i < format_length;) {
        if ( format[i] == '%' ) {
            int start = i;

            struct format f;
            f.spec = unknown_spec;
            f.plus = 0;
            f.minus = 0;
            f.space = 0;
            f.width = 0;
            f.precision = -1;
            f.length = unknown_len;

            i++;
            i += extract_flags(format + i, &f);
            i += extract_width(format + i, &f);
            i += extract_precision(format + i, &f);
            i += extract_length(format + i, &f);
            i += extract_spec(format + i, &f);

            if ( f.spec == unknown_spec ) {
                char local[2] = {format[start], '\0'};
                s21_strcat(str, local);
                i = start + 1;
            } else {
                char* spec = spec_string(f, &args);
                s21_strcat(str, spec);
                free(spec);
            }

        } else {
            char local[2] = {format[i], '\0'};
            s21_strcat(str, local);
            i++;
        }
    }
    va_end(args);
    return s21_strlen(str);
}

int extract_flags(const char* format, struct format *f) {
    int flags_len = s21_strspn(format, "+- ");
    for ( int i = 0; i < flags_len; i++ ) {
        switch ( format[i] ) {
            case '+':
                f -> plus += 1;
                break;
            case '-':
                f -> minus += 1;
                break;
            case ' ':
                f -> space += 1;
                break;
            default:
                break;
        }
    }
    return flags_len;
}


int extract_width(const char* format, struct format *f) {
    int number_len = s21_strspn(format, "0123456789");
    if ( number_len != 0 ) {
        f -> width = s21_atoi(format, number_len);
    }
    return number_len;
}

int extract_precision(const char* format, struct format *f) {
    int dot_found = 0;
    int number_len = 0;
    if ( *format == '.' ) {
        dot_found = 1;
        number_len = s21_strspn(format + 1, "0123456789");
        if ( number_len == 0 ) {
            f -> precision = 0;
        } else {
            f -> precision = s21_atoi(format + 1, number_len);
        }
    }
    return dot_found + number_len;
}

int extract_length(const char* format, struct format *f) {
    int length_found;
    switch ( *format ) {
        case 'l':
            length_found = 1;
            f -> length = l_len;
            break;
        case 'h':
            length_found = 1;
            f -> length = h_len;
            break;
        default:
            length_found = 0;
            break;
    }
    return length_found;
}

int extract_spec(const char* format, struct format *f) {
    int spec_found = 1;
    switch ( *format ) {
        case 'c':
            f->spec = c_spec;
            break;
        case 'd':
            f->spec = d_spec;
            break;
        case 'i':
            f->spec = i_spec;
            break;
        case 'f':
            f->spec = f_spec;
            break;
        case 's':
            f->spec = s_spec;
            break;
        case 'u':
            f->spec = u_spec;
            break;
        case '%':
            f->spec = percent_spec;
            break;
        default:
            spec_found = 0;
            break;
    }
    return spec_found;
}


int s21_atoi(const char* str, int n) {
    int result = 0;
    int mult = 1;
    for ( int i = n; i > 0; i-- ) {
        result += (str[i - 1] - 48) * mult;
        mult *= 10;
    }
    return result;
}

char* spec_string(struct format f, va_list* args) {
    char* result;
    switch ( f.spec ) {
    case d_spec:
        result = spec_d(f, args);
        break;
    case i_spec:
        result = spec_d(f, args);
        break;
    case u_spec:
        result = spec_u(f, args);
        break;
    case s_spec:
        result = spec_s(f, args);
        break;
    case c_spec:
        result = spec_c(args);
        break;
    case f_spec:
        result = spec_f(f, args);
        break;
    case percent_spec:
        result = calloc(2, sizeof(char));
        result[0] = '%';
        break;
    default:
        result = calloc(1, 1);
        break;
    }
    char* adjusted_result;
    if ( f.spec != percent_spec ) {
        adjusted_result = adjusted_width(f, result);
        free(result);
    } else {
        adjusted_result = result;
    }
    return adjusted_result;
}

char* spec_d(struct format f, va_list* args) {
    long int n;

    if (f.length == h_len) {
        n = (short) va_arg(*args, int);
    } else if (f.length == l_len) {
        n = va_arg(*args, long);
    } else {
        n = va_arg(*args, int);
    }

    char* str = s21_itoa(n);

    char* str_with_precision = adjusted_precision_for_int(f, str);
    free(str);

    s21_size_t number_len = s21_strlen(str_with_precision);
    char* result = calloc(number_len + 2, sizeof(char));

    if ( n < 0 ) {
        result[0] = '-';
    } else if (f.plus == 0 && f.space > 0) {
        result[0] = ' ';
    } else if (f.plus > 0) {
        result[0] = '+';
    }

    s21_strcat(result, str_with_precision);
    free(str_with_precision);

    return result;
}

char* s21_itoa(long int c) {
    if ( c < 0 ) {
        c = -c;
    }

    long int a = 10;
    long int i = 1;
    long int tmp = c;

    while (1) {
        long int quot = tmp / a;
        if ( quot != 0 ) {
            i += 1;
            tmp = quot;
        } else {
            break;
        }
    }

    char* str = calloc((i + 1), sizeof(char));

    tmp = c;
    for ( int j = i - 1; j >= 0; j-- ) {
        long int rem = tmp % a;

        str[j] = rem + 48;
        tmp = tmp / a;
    }

    str[i] = '\0';
    return str;
}


char* spec_u(struct format f, va_list* args) {
    unsigned long int n;

    if (f.length == h_len) {
        n = (unsigned short) va_arg(*args, unsigned int);
    } else if (f.length == l_len) {
        n = va_arg(*args, unsigned long);
    } else {
        n = va_arg(*args, unsigned int);
    }
    char* str = s21_itoa_unsigned(n);
    char* str_with_precision = adjusted_precision_for_int(f, str);
    free(str);
    s21_size_t number_len = s21_strlen(str_with_precision);
    char* result = calloc(number_len + 2, sizeof(char));
    if (f.plus == 0 && f.space > 0) {
        result[0] = ' ';
    } else if (f.plus > 0) {
        result[0] = '+';
    }
    s21_strcat(result, str_with_precision);
    free(str_with_precision);
    return result;
}

char* s21_itoa_unsigned(unsigned long int c) {
    unsigned long int a = 10;
    unsigned long int i = 1;
    unsigned long int tmp = c;
    while (1) {
        unsigned long int quot = tmp / a;
        if ( quot != 0 ) {
            i += 1;
            tmp = quot;
        } else {
            break;
        }
    }
    char* str = calloc((i + 1), sizeof(char));
    tmp = c;
    for ( int j = i - 1; j >= 0; j-- ) {
        unsigned long int rem = tmp % a;

        str[j] = rem + 48;
        tmp = tmp / a;
    }
    str[i] = '\0';
    return str;
}

char* spec_s(struct format f, va_list* args) {
    char* str = va_arg(*args, char*);
    char* str_with_precision = adjusted_precision_for_string(f, str);
    return str_with_precision;
}

char* spec_c(va_list* args) {
    char* str = calloc(2, sizeof(char));
    int c = va_arg(*args, int);
    str[0] = c;
    return str;
}

char* adjusted_width(struct format f, const char* str) {
    s21_size_t str_len = s21_strlen(str);
    char* result;
    if (f.width == 0) {
        result = calloc(str_len + 1, sizeof(char));
        s21_strcat(result, str);
    } else {
        s21_size_t result_length = str_len > (s21_size_t)f.width ? str_len : (s21_size_t)f.width;
        s21_size_t diff_len = str_len > (s21_size_t)f.width ? str_len - (s21_size_t)f.width : \
            (s21_size_t)f.width - str_len;
        result = calloc(result_length + 1, sizeof(char));
        if (str_len > (s21_size_t)f.width) {
            s21_strcat(result, str);
        } else if (f.minus == 0) {
            s21_memset(result, ' ', diff_len);
            s21_strcat(result, str);
        } else {
            s21_strcat(result, str);
            s21_memset(result + str_len, ' ', diff_len);
        }
    }
    return result;
}

char* adjusted_precision_for_int(struct format f, const char* str) {
    s21_size_t str_len = s21_strlen(str);
    char* result;
    if (f.precision == -1) {
        result = calloc(str_len + 1, sizeof(char));
        s21_strcat(result, str);
    } else {
        s21_size_t result_length = str_len > (s21_size_t)f.precision ? str_len : (s21_size_t)f.precision;
        s21_size_t diff_len = str_len > (s21_size_t)f.precision ? str_len - (s21_size_t)f.precision : \
            (s21_size_t)f.precision - str_len;
        result = calloc(result_length + 1, sizeof(char));
        if (f.precision == 0 && str_len == 1 && str[0] == '0') {
            // precision 0 для числа 0 возвращает пустую строку, ничего не делаем с result
        } else if (str_len < (s21_size_t)f.precision) {
            s21_memset(result, '0', diff_len);
            s21_strcat(result, str);
        } else {
            s21_strcat(result, str);
        }
    }
    return result;
}


char* adjusted_precision_for_string(struct format f, const char* str) {
    s21_size_t str_len = s21_strlen(str);
    char* result;
    if (f.precision == -1) {
        result = calloc(str_len + 1, sizeof(char));
        s21_strcat(result, str);
    } else {
        s21_size_t result_length = str_len < (s21_size_t)f.precision ? str_len : (s21_size_t)f.precision;
        result = calloc(result_length + 1, sizeof(char));
        s21_strncat(result, str, result_length);
    }
    return result;
}


char* spec_f(struct format f, va_list* args) {
    if (f.precision == -1) {
        f.precision = 6;
    }

    double rounder = 0.5;
    int rounder_n = f.precision;
    while (rounder_n > 0) {
        rounder /= 10;
        rounder_n--;
    }

    int sign;
    double n = va_arg(*args, double);

    if (n < 0) {
        sign = -1;
    } else {
        sign = 1;
    }

    n = n * sign + rounder;

    long integer = (long) n;
    double remain = n - integer;

    char* integer_str = s21_itoa(integer);
    s21_size_t integer_len = s21_strlen(integer_str);

    char* remain_str = calloc(f.precision + 1, sizeof(char));

    int i = 0;
    while (i < f.precision) {
        double multiplied_remain = remain * 10;
        char num = (int) multiplied_remain + 48;
        remain_str[i] = num;
        remain = multiplied_remain - (int) multiplied_remain;
        i++;
    }

    char* result = calloc(integer_len + f.precision + 3, sizeof(char));


    if ( sign == -1 ) {
        result[0] = '-';
    } else if (f.plus == 0 && f.space > 0) {
        result[0] = ' ';
    } else if (f.plus > 0) {
        result[0] = '+';
    }

    s21_strcat(result, integer_str);
    if (f.precision != 0) {
        result[s21_strlen(result)] = '.';
    }
    s21_strcat(result, remain_str);

    free(integer_str);
    free(remain_str);

    return result;
}
