#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* Flags */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* Size modifiers */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - structure that contains format specifiers
 * and their handling functions
 *
 * @fmt: format specifier
 * @fn: handling function
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct fmt fmt_t;

int _printf(const char *format, ...);

/* Handle all format specifiers */
int handle_print(const char *fmt, int *i,
		va_list list, char buffer[], int flags, int width, int precision, int size);

/* Handle specifiers-- %, c, s, i, p, d, b, o, h */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size);

int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);

int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size);

int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size);

int print_binary(va_list types, char buffer[],
			int flags, int width, int precision, int size);

int print_octal(va_list types, char buffer[],
			int flags, int width, int precision, int size);

int print_hexadecimal(va_list types, char buffer[],
			int flags, int width, int precision, int size);

int print_hexa_upper(va_list types, char buffer[],
			int flags, int width, int precision, int size);


int print_hexa(va_list types, char map_to[],
		char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Handle unsigned types */
int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* Handles non-printable characters */
int print_non_printable(va_list types, char buffer[],
			int flags, int width, int precision, int size);


/* Handle flags, mini field width, precision and size modifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Handles reversed str */
int print_reverse(va_list types, char buffer[],
			int flags, int width, int precision, int size);

/*Handles rot13'ed str */
int print_rot13string(va_list types, char buffer[],
			int flags, int width, int precision, int size);

/* Write formatted out to standard output */
int handle_write_char(char c, char buffer[],
			int flags, int width, int precision, int size);
int write_number(int is_positive, int i, char buffer[],
			int flags, int width, int precision, int size);
int write_num(int i, char buffer[], int flags, int width, int precision,
			int length, char pad, char extra_c);
int write_pointer(char buffer[], int i, int length,
			int width, int flags, char pad, char extra_c, int pad_start);

int write_unsgnd(int is_negative, int i, char buffer[],
		int flags, int width, int precision, int size);

/* Check if c is printable or digit */
int is_printable(char);
int is_digit(char);

int append_hexa_code(char, char[], int);

/* Handle type and size modifications */
long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif
