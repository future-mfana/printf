#include "main.h"
#include <stdarg.h>

/**
 * print_octal - prints an unsigned octal num
 * @types: arg list
 * @buffer: array
 * @flags: flags
 * @width: field width
 * @precision: precision
 * @size: size modifier
 *
 * Return: num of char printed
 */

int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int start_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && start_num != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

