#ifndef SRC_S21_STRING_H_
#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>
#include"s21_sprintf.h"
#define SRC_S21_STRING_H_
#define s21_NULL ((void *)0)
typedef long unsigned int s21_size_t;

void *s21_memchr(const void *str, int f, s21_size_t n);
int s21_memcmp(const void *str1, const void* str2, s21_size_t n);
void *s21_memcpy(void* dest, const void* str1, s21_size_t n);
void *s21_memmove(void *dest, void *str1, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strpbrk(const char *str, const char *sym);
char *s21_strrchr(const char* str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
s21_size_t s21_strlen(const char *str);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strtok(char * str, const char *delim);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
size_t s21_from_end_strspn(const char *str1, const char *str2);


#endif  // SRC_S21_STRING_H_
