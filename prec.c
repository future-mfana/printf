#include "main.h"
#include <stdarg.h>

/**
 * get_precision - calculates the printing precision
 * @format: format  format specifer
 * @i: list of args to be printed
 * @list: list of args
 *
 * Return: precision
 */

int get_precision(const char *format, int *i, va_list list)
{
	int current_arg = *i + 1;
	int precision = -1;

	if (format[current_arg] != '.')
		return (precision);

	precision = 0;

	for (current_arg += 1; format[current_arg] != '\0'; current_arg++)
	{
		if (is_digit(format[current_arg]))
		{
			precision *= 10;
			precision += format[current_arg] - '0';
		}
		else if (format[current_arg] == '*')
		{
			current_arg++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = current_arg - 1;
	return (precision);
}

/**
 * is_digit - verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
