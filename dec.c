#include "main.h"
#include <stdarg.h>

/**
 * print_int - prints int
 * @types: arg list
 * @buffer: array
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: num of printed chars
 */

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_neg = 0;
	long int l = va_arg(types, long int);
	unsigned long int num;

	l = convert_size_number(l, size);
	if (l == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)l;

	if (l < 0)
	{
		num = (unsigned long int)((-1) * l);
		is_neg = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;

	return (write_number(is_neg, i, buffer, flags, width, precision, size));
}

/**
 * write_number - prints a string
 * @is_negative: arg list
 * @i: array index
 * @buffer: array to handle print
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: num of printed chars
 */

int write_number(int is_negative, int i, char buffer[],
			int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - i - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(i, buffer, flags, width,
				precision, length, pad, extra_ch));
}

/**
 * write_num - writes num to stdout
 * @i: starting buffer index
 * @buffer: buffer
 * @flags: flags
 * @width: width
 * @precision: precision
 * @length: number length
 * @pad: padding char
 * @extra_c: extra char
 *
 * Return: num of printed chars
 */

int write_num(int i, char buffer[], int flags, int width,
		int precision, int length, char pad, char extra_c)
{
	int x, pad_start = 1;

	if ((precision == 0) && (i == BUFF_SIZE - 2) &&
			(buffer[i] == '0') && (width == 0))
		return (0);
	if ((precision == 0) && (i == BUFF_SIZE - 2) &&
			(buffer[i] == '0'))
		buffer[i] = pad = ' ';
	if ((precision > 0) && (precision < length))
		pad = ' ';
	while (precision > length)
		buffer[--i] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buffer[x] = pad;
		buffer[x] = '\0';
		if ((flags & F_MINUS) && pad == ' ')
		{
			if (extra_c)
				buffer[-i] = extra_c;
			return (write(1, &buffer[i], length) + write(1, &buffer[1], x - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[1], x - 1) + write(1, &buffer[i], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
					write(1, &buffer[i], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--i] = extra_c;
	return (write(1, &buffer[i], length));
}
