#include "main.h"
#include <stdarg.h>
#include <stddef.h>

/**
 * print_rot13string - prints a str in rot13
 * @types: list of args
 * @buffer: buffer of array
 * @flags: active flags
 * @width: width
 * @precision: precision specifier
 * @size: size specifier
 *
 * Return: number of chars
 */

int print_rot13string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char x, *str;
	unsigned int i, j;

	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				x = output[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}


