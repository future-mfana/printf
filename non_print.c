#include "main.h"

/**
 * print_non_printable - prints ASCII code in hexa of
 * non-printable chars
 * @types: arg list
 * @buffer: array
 * @flags: active flags
 * @width: width specifier
 * @precision: precision specifier
 * @size: size specifier
 *
 * Return: printed chars
 */

int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * is_printable - checks if a char is printable
 * @c: char to be checked
 *
 * Return: 1 if c is printable, 0 otherwise
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - appends ASCII in hexadecimal code
 * to an array
 * @buffer: array of chars
 * @i: index at which to start appending
 * @ascii_code: ASCII CODE
 *
 * Return: Always 3
 */

int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}


