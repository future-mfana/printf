#include "main.h"

/**
 * print_hexadecimal - prints an unsigned hexadecimal
 * @types: arg list
 * @buffer: array
 * @flags: active flags
 * @width: width specifier
 * @precision: precision specifier
 * @size: size specifier
 *
 * Return: printed chars
 */

int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}


/**
 * convert_size_unsgnd - converts number to a specified size
 * @num: number
 * @size: size
 *
 * Return: converted num
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: negative number
 * @ind: starting index
 * @buffer: char array
 * @flags: active flags
 * @width: Width specifier
 * @precision: precision specifier
 * @size: size specifier
 *
 * Return: written chars
 */

int write_unsgnd(int is_negative, int i, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - i - 1, x = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if ((precision == 0) && (i == BUFF_SIZE - 2) && buffer[i] == '0')
		return (0);
	if ((precision > 0) && (precision < length))
		pad = ' ';

	while (precision > length)
	{
		buffer[--i] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[x] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS)
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], x));
		else
			return (write(1, &buffer[0], i) + write(1, &buffer[i], length));
	}
	return (write(1, &buffer[i], length));
}
