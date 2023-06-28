#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void print_buffer(char buffer[], int *buff_i);

/**
 * _printf - produces output according to a format
 * @format: format str
 * Return: num of chars to stdin
 */

int _printf(const char *format, ...)
{
	int i, printed_char = 0, printed_chars = 0;
	int flags, width, precision, size;
	va_list list;
	char buffer[BUFF_SIZE];
	int buff_i = 0;

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_i++] = format[i];
			if (buff_i == BUFF_SIZE)
				print_buffer(buffer, &buff_i);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed_char = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed_char == -1)
				return (-1);
			printed_chars += printed_char;
		}
	}

	print_buffer(buffer, &buff_i);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - prints the contents of the buffer
 * @buffer: array
 * @buff_i: index at which the next char is added
 */
void print_buffer(char buffer[], int *buff_i)
{
	if (*buff_i > 0)
		write(1, &buffer[0], *buff_i);

	*buff_i = 0;
}

/**
 * get_size - calculates the size to cast the argument
 * @format: format str
 * @i: format str length
 *
 * Return: precision
 */

int get_size(const char *format, int *i)
{
	int current_arg = *i + 1;
	int size = 0;

	if (format[current_arg] == 'l')
		size = S_LONG;
	else if (format[current_arg] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_arg - 1;
	else
		*i = current_arg;

	return (size);
}

/**
 * handle_print - prints an argument based on its type
 * @fmt: format specifier
 * @list: arg list
 * @i: index
 * @buffer: array
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: 1 or 2;
 */

int handle_print(const char *fmt, int *i, va_list list,
		char buffer[], int flags, int width, int precision, int size)
{
	int x, len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (x = 0; fmt_types[x].fmt != '\0'; x++)
		if (fmt[*i] == fmt_types[x].fmt)
			return (fmt_types[x].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[x].fmt == '\0')
	{
		if (fmt[*i] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*i - 1] == ' ')
			len += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (fmt[*i] != ' ' && fmt[*i] != '%')
				--(*i);
			if (fmt[*i] == ' ')
				--(*i);
			return (1);
		}
		len += write(1, &fmt[*i], 1);
		return (len);
	}
	return (printed_chars);
}
