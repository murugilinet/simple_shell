#include "shell.h"

/**
 * expand_var- expands variables
 * @data: pointer to struct of programs data
 * Return: nothing
 * but sets errno
 */
void expand_var(info *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input == NULL)
		return;
	add_buffer(line, data->input);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			num_to_string(errno, exp, 10);
			add_buffer(line, exp);
			add_buffer(line, data->input + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] =  '\0';
			num_to_string(getpid(), exp, 10);
			add_buffer(line, exp);
			add_buffer(line, data->input + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				exp[j - 1] = line[i + j];
			tmp = env_get_var(exp, data);
			line[i] = '\0', exp[0] = '\0';
			add_buffer(exp, line + i + j);
			tmp ? add_buffer(line, tmp) : 1;
			add_buffer(line, exp);
		}
	if (!str_cmp(data->input, line, 0))
	{
		free(data->input);
		data->input = str_duplicate(line);
	}
}
/**
 * exp_alias- expands alises
 * @data: pointer to a struct of programs data
 * Return: nothing
 * sets errno
 */
void exp_alias(info *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input == NULL)
		return;
	add_buffer(line, data->input);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			exp[j] = line[i + j];
		exp[j] = '\0';

		tmp = get_alias(data, exp);
		if (tmp)
		{
			exp[0] = '\0';
			add_buffer(exp, line + i + j);
			line[i] = '\0';
			add_buffer(line, tmp);
			line[str_len(line)] = '\0';
			add_buffer(line, exp);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input);
		data->input = str_duplicate(line);
	}
}

/**
 * add_buffer- adds string at end of buffer
 * @buffer: buffer to be filled
 * @str_add: atring to be copied in the buffer
 * Return: length after additional to buffer
 * sets errno
 */
int add_buffer(char *buffer, char *str_add)
{
	int len, i;

	len = str_len(buffer);
	for (i = 0; str_add[i]; i++)
	{
		buffer[len + i] = str_add[i];
	}
	buffer[len + i] = '\0';
	return (len + i);
}
