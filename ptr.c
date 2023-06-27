#include "main.h"

/**
 * print_pointer - Prints address of an arg in memory
 * @types: type of args
 * @buffer: char array
 * @flags: active flags
 * @width: width specifier
 * @precision: Precision specifier
 * @size: size specifier
 *
 *Return: printed chars
 */

int print_pointer(va_list types, char buffer[],
			int flags, int width, int precision, int size)
{
	char extra_c = 0;
	char pad = ' ';
	unsigned long num_address;
	int ind = BUFF_SIZE - 2;
	int length = 2;
	int pad_start = 1;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_address = (unsigned long)address;
	while (num_address > 0)
	{
		buffer[ind--] = map_to[num_address % 16];
		num_address /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
	{
		extra_c = '+';
		length++;
	}
	else if (flags & F_SPACE)
	{
		extra_c = ' ';
		length++;
	}
	ind++;
	return (write_pointer(buffer, ind, length, width,
				flags, pad, extra_c, pad_start));
}

/**
 * write_pointer - writes a memory address
 * @buffer: char array
 * @ind: starting buffer index
 * @length: length of nummber
 * @width: width specifier
 * @flags: active flags
 * @pad: char padding
 * @extra_c: extra char
 * @pad_start: starting padding index
 *
 * Return: number of written chars
 */

int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char pad, char extra_c, int pad_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = pad;
		buffer[i] = '\0';

		if (flags & F_MINUS && pad == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], i - pad_start) +
					write(1, &buffer[ind], length - (1 - pad_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
