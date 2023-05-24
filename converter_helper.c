#include "shell.h"
/**
 * _atoi- converts string to number.
 * @str: pointer to string origin.
 * Return: int of string or 0.
 */
int _atoi(char *str)
{
	unsigned int number = 0;
	int sign = 1;

	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sign *= -1;
		if (*str == '+')
			sign *=  +1;
		str++;
	}

	while ('0' <= *str && *str <= '9' && *str != '\0')
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign);
}
/**
 * num_to_string- converts a number to string
 * @number: number to be converted to string
 * @str: buffer to save the number as string
 * @base: base to convert number
 * Return: nothing
 */
void num_to_string(long number, char *str, int base)
{
	int index = 0, isnegative  = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		str[index++] = '0';

	if (str[0] == '-')
		isnegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			str[index++] = letters[-(cociente % base)];
		else
			str[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (isnegative)
		str[index++] = '-';

	str[index] = '\0';
	str_rev(str);
}
/**
 * count_character- count the coincidences of characters in string
 * @str: pointer to string origin
 * @character: string with chars
 * Return: int of string or 0
 */
int count_character(char *str, char *character)
{
	int i, count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == character[0])
			count++;
	}
	return (count);
}
