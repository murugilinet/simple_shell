#include "shell.h"
/**
 * str_len- gets length of a string.
 * @str: pointer to string.
 * Return: length of string.
 */
int str_len(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);
	while (str[length++] != '\0')
	{
	}
	return (--length);

}

/**
 * str_cmp- compares two strings
 * @str1: first string
 * @str2: second string
 * @num: number of characters to be compared,
 * 0 if infinite
 * Return: 1 if the strings are equal
 * 0 otherwise
 */
int str_cmp(char *str1, char *str2, int num)
{
	int i;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (num == 0) /*infinite*/
	{
		if (str_len(str1) != str_len(str2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
	else /*when theres a specific num of characters to be compared*/
	{
		for (i = 0; i < num; i++)
		{
			if (str1[i] != str2[i])
			return (0);
		}
		return (1);
	}
}
/**
 * str_cat- concatenates two strings
 * @str1: first string
 * @str2: string to be concated
 * Return: pointer to the new array
 */
char *str_cat(char *str1, char *str2)
{
	char *new_str;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_len(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = str_len(str2);

	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_str == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; str1[len1] != '\0'; len1++)
		new_str[len1] = str1[len1];
	free(str1);

	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		new_str[len1] = str2[len2];
		len1++;
	}
	new_str[len1] = '\0';
	return (new_str);
}
/**
 * str_duplicate- duplicates a string
 * @str: string to be duplicated
 * Return: pointer to the new array
 */
char *str_duplicate(char *str)
{
	char *new_str;
	int len, i;

	if (str == NULL)
		return (NULL);
	len = str_len(str) + 1;
	new_str = malloc(sizeof(char) * len);

	if (new_str == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
		new_str[i] = str[i];
	return (new_str);
}
/**
 * str_rev- reverses a string
 * @str: pointer to string to be reversed
 * Return: void
 */
void str_rev(char *str)
{
	int i = 0, len;
	char tmp;

	len = str_len(str) - 1;

	while (i < len)
	{
		tmp = str[i];
		str[i++] = str[len];
		str[len--] = tmp;
	}
}
