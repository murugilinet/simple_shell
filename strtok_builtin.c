#include "shell.h"
/**
 * _strtok - separates strings with delimiters
 * @line: pointer to array we receive in getline.
 * @delim: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}

	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}

/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(info *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = str_len(data->input);
	if (length)
	{
		if (data->input[length - 1] == '\n')
			data->input[length - 1] = '\0';
	}

	for (i = 0; data->input[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input[i] == delimiter[j])
				counter++;
		}
	}

	data->token = malloc(counter * sizeof(char *));
	if (data->token == NULL)
	{
		perror(data->prog_name);
		exit(errno);
	}
	i = 0;
	data->token[i] = str_duplicate(_strtok(data->input, delimiter));
	data->cmd_name = str_duplicate(data->token[0]);
	while (data->token[i++])
	{
		data->token[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}
