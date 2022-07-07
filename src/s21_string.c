#include"s21_string.h"
#include"s21_strerror.h"

// 1
void *s21_memchr(const void *str, int f, s21_size_t n) {
    const unsigned char *buf = str;
    s21_size_t i;
    for ( i = 0; i < n; i++ ) {
        if ( buf[i] == f ) {
            return (void*) buf + i;
        }
    }
    return s21_NULL;
}

// 2
int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
    const unsigned char *buf1 = str1;
    const unsigned char *buf2 = str2;
    s21_size_t i, back;
    back = 0;
    for (i = 0; i < n; i++) {
        if (*buf1 == *buf2) {
            buf1++;
            buf2++;
      } else {
            back = (*buf1-*buf2);
        }
    }
    return back;
}

// 3
void *s21_memcpy(void* dest, const void* str1, s21_size_t n) {
    char *d = dest;
    const unsigned char *buf = str1;
    for ( s21_size_t i = 0; i < n; i++ ) {
        d[i] = buf[i];
    }
    return dest;
}

// 4
void *s21_memmove(void *dest, void *str1, s21_size_t n) {
    void *d = dest;
    if (dest <= str1 || (char*)dest >= ((char*)str1 + n)) {
        while (n--) {
            *(char*)dest++ = *(char*)str1++;
        }
  } else {
        dest = (char*)dest + n - 1;
        str1 = (char*)str1 + n - 1;
        while (n--) {
            *(char*)dest-- = *(char*)str1--;
        }
    }
    return d;
}

// 5
void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *d = str;
    const unsigned char zc = c;
    for (s21_size_t i = 0; i < n; i++) {
        *d++ = zc;
    }
    return str;
}

// 6
char *s21_strcat(char *dest, const char *src) {
    s21_size_t length_dest = s21_strlen(dest);
    s21_size_t length_src = s21_strlen(src);
    s21_memcpy(dest + length_dest, src, length_src + 1);
    return dest;
}

// 7
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t length_dest = s21_strlen(dest);
    s21_size_t length_src = s21_strlen(src);
    if (n > length_src) {
        n = length_src;
    }
    s21_memcpy(dest + length_dest, src, n);
    dest[length_dest + n] = '\0';
    return dest;
}

// 8
char *s21_strchr(const char *str, int c) {
    const char t = c;
    char *buf;
    for (; ; str++) {
        if (*str == t) {
            buf = (char*)str;
            break;
        }
        if (*str == '\0') {
            buf = s21_NULL;
            break;
        }
    }
    return buf;
}

// 9
int s21_strcmp(const char *str1, const char *str2) {
    s21_size_t length_str1 = s21_strlen(str1);
    s21_size_t length_str2 = s21_strlen(str2);
    int result = 0;
    if ( length_str1 == length_str2 ) {
        result = s21_memcmp(str1, str2, length_str1);
    } else if ( length_str1 > length_str2 ) {
        result = s21_memcmp(str1, str2, length_str1);
    } else {
        result = s21_memcmp(str1, str2, length_str2);
    }
    return result;
}

// 10
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    s21_size_t lenght_str1 = s21_strlen(str1);
    s21_size_t length_str2 = s21_strlen(str2);
    // находим максимальную на тот случай, если n > какой-либо из длин
    s21_size_t max_length = lenght_str1 > length_str2 ? lenght_str1 : length_str2;
    if ( n > max_length ) {
        result = s21_memcmp(str1, str2, max_length);
    } else {
         result = s21_memcmp(str1, str2, n);
    }
    return result;
}

// 11
char *s21_strcpy(char *dest, const char *src) {
    s21_size_t length_src = s21_strlen(src) + 1;
    return s21_memcpy(dest, src, length_src);
}

// 12
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t length_src = s21_strlen(src);
    if ( length_src >= n ) {
        s21_memcpy(dest, src, n);
    } else {
        s21_memcpy(dest, src, length_src);
        s21_memset(dest + length_src, '\0', n - length_src);
    }
    return dest;
}

// 13
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t length_str1 = s21_strlen(str1);
    s21_size_t length_str2 = s21_strlen(str2);
    s21_size_t min_length = length_str1;
    for ( s21_size_t i = 0; i < length_str2; i++ ) {
        char* occurrence =  s21_memchr(str1, str2[i], length_str1);
        if ( occurrence != s21_NULL ) {
            s21_size_t tmp = occurrence - str1;
            min_length = min_length > tmp ? tmp : min_length;
        }
    }
    return min_length;
}


// 14
char *s21_strerror(int errnum) {
    char* error = s21_NULL;
    if (errnum < MAX_ERRORS && errnum >= 0) {
        error = ERRORS[errnum];
    } else {
        s21_sprintf(SPACE, "%s %d", STR_ERROR, errnum);
        error = SPACE;
    }
    return error;
}

// 15
s21_size_t s21_strlen(const char *str) {
    int result;
    for ( result = 0; str[result] != '\0'; result++ ) ;
    return result;
}

// 16
char *s21_strpbrk(const char *str1, const char *str2) {
    const char *buf1 = str1;
    const char *buf2 = str2;
    char *back = s21_NULL;
    while (*buf1 != '\0') {
        buf2 = str2;
        while (*buf2 != '\0') {
            if (*buf2 == *buf1) {
                back = (char*)buf1;
                break;
            }
            buf2++;
        }
        if (*buf2 == *buf1) {
                break;
            }
        buf1++;
    }
    return back;
}

// 17
char *s21_strrchr(const char* str, int c) {
    const char f = c;
    const char *buf = s21_NULL;
    for (; ; ++str) {
        if (*str == f) {
            buf = str;
        }
        if (*str == '\0') {
            break;
        }
    }
    return (char*)buf;
}

// 18
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t result = 0;
    s21_size_t str1_length = s21_strlen(str1);
    s21_size_t str2_length = s21_strlen(str2);
    for ( s21_size_t i = 0; i < str1_length; i++ ) {
        if (s21_memchr(str2, str1[i], str2_length) != s21_NULL) {
            result+=1;
        } else {
            break;
        }
    }
    return result;
}

// 19 half WORK YA NE EBU POCH
char *s21_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return ((char*)haystack);
    }
    for (; (haystack = s21_strchr(haystack, *needle)) != s21_NULL; ++haystack) {
        const char *str1, *str2;
        for (str1 = haystack, str2 = needle; ;) {
            if (*++str2 == '\0') {
                return ((char*)haystack);
          } else if (*++str1 != *str2) {
                break;
            }
        }
    }
    return s21_NULL;
}

// 20
char *s21_strtok(char * str, const char *delim) {
    static char * s = s21_NULL;
    char * ret = s21_NULL;
    if (str != s21_NULL) {
      s = str;
    }
    if (s != s21_NULL && s21_strlen(s)) {
        const s21_size_t dlen = s21_strlen(delim);
        while (*s && s21_memchr(delim, *s, dlen) != s21_NULL) {
          ++s;
        }
        if (*s) {
            ret = s;
            while (*s) {
                if (s21_memchr(delim, *s, dlen) != s21_NULL) {
                    break;
              } else {
                    ++s;
                }
            }
            if (*s) {
                s[0] = 0;
                ++s;
            }
        }
    }
    return ret;
}

// 21
void *s21_to_upper(const char *str) {
    s21_size_t str_length = s21_strlen(str);
    char *result = (char*) malloc(sizeof(char) * (str_length + 1));
    s21_strcpy(result, str);
    while (*str) {
        if ( *str >= 'a' && *str <= 'z' ) {
            *result = *str - 32;
        }
        str++;
        result++;
    }
    return result - str_length;
}

// 22
void *s21_to_lower(const char *str) {
    s21_size_t str_length = s21_strlen(str);
    char* result = (char *) malloc(sizeof(char) * (str_length + 1));
    s21_strcpy(result, str);
    while (*str) {
        if ( *str >= 'A' && *str <= 'Z' ) {
            *result = *str + 32;
        }
        str++;
        result++;
    }
    return result - str_length;
}

// 23
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    // Exceptions:
    // ArgumentNullException: If the String value is null.
    // ArgumentOutOfRangeException: If Indexvalue is negative or greater than the length of the string.
    s21_size_t src_length = s21_strlen(src);
    s21_size_t str_length = s21_strlen(str);
    char* result = s21_NULL;
    if ( start_index <= src_length ) {
        result = (char*)malloc(sizeof(char) * (src_length + str_length + 1));
        s21_strncpy(result, src, start_index);
        s21_strncpy(result + start_index, str, str_length);
        s21_strncpy(result + start_index + str_length, src + start_index, src_length - start_index);
        *(result + src_length + str_length) = '\0';
    }
    return result;
}

// 24
void *s21_trim(const char *src, const char *trim_chars) {
    s21_size_t src_length = s21_strlen(src);
    char* result = s21_NULL;
    s21_size_t spn = s21_strspn(src, trim_chars);
    s21_size_t spn_from_end = s21_from_end_strspn(src, trim_chars);
    if ( spn == src_length ) {
        result = (char*)calloc(1, 1);
    } else {
        result = (char*)calloc(src_length + 1, sizeof(char));
        s21_strncpy(result, src + spn, src_length - spn_from_end - spn);
    }
    return result;
}

s21_size_t s21_from_end_strspn(const char *str1, const char *str2) {
    s21_size_t result = 0;
    s21_size_t str1_length = s21_strlen(str1);
    s21_size_t str2_length = s21_strlen(str2);
    for ( s21_size_t i = str1_length - 1; i > 0; i-- ) {
        if (s21_memchr(str2, str1[i], str2_length) != s21_NULL) {
            result += 1;
        } else {
            break;
        }
    }
    return result;
}
