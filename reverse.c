#include "main.h"
#include <stdarg.h>
#include <stddef.h>

/**
 * print_reverse - prints reversed str
 * @types: arg list
 * @buffer: array
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: number of chars printed
 */

int print_reverse(va_list types, char buffer[], int flags,
		 int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char j = str[i];

		write(1, &j, 1);
		count++;
	}
	return (count);
}
