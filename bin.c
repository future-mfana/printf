#include "main.h"
#include <stdarg.h>

/**
 * print_binary - converts unsigned int to binary
 * @types: arg list
 * @buffer: array
 * @flags: active flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: num chars printed
 */

int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int a, b, i, sum;
	unsigned int arr[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(types, unsigned int);
	b = 2147483648; /* 2 raised to 32 - 1 */
	arr[0] = a / b;
	for (i = 1; i < 32; i++)
	{
		a /= 2;
		arr[i] = (a / b) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += arr[i];
		if (sum || i == 31)
		{
			char c = '0' + arr[i];

			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}

