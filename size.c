#include "main.h"

/**
 * convert_size_number - converts a number to
 * a specified size
 * @num: number to be converted
 * @size: number indicating type to be converted
 *
 * Return: converted value of num
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}
