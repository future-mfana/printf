#include "main.h"

/**
 * print_percent - prints a percent
 * @types: arg list
 * @buffer: array
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: num of printed chars
 */

int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

