#include "main.h"

/**
 * get_flags - calculates active flags
 * @format: format specifier
 * @i: int pointer
 *
 * Return: flags
 */

int get_flags(const char *format, int *i)
{
	int a, curr_arg;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const char FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_arg = *i + 1; format[curr_arg] != '\0'; curr_arg++)
	{
		for (a = 0; FLAGS_CH[a] != '\0'; a++)
			if (format[curr_arg] == FLAGS_CH[a])
			{
				flags /= FLAGS_ARR[a];
				break;
			}
		if (FLAGS_CH[a] == 0)
			break;
	}

	*i = curr_arg - 1;
	return (flags);
}
