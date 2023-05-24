#include "shell.h"

/**
 * print_alias - add, remove or show aliases.
 * @data: struct for the program's data.
 * @alias_name : name of the alias to be printed.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(info *data, char *alias_name)
{
	int i, j, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_len(alias_name);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias_name || (str_cmp(data->alias_list[i], alias_name, alias_len)
				&&	data->alias_list[i][alias_len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_buffer(buffer, "'");
				add_buffer(buffer, data->alias_list[i] + j + 1);
				add_buffer(buffer, "'\n");
				_prints(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias_name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(info *data, char *alias_name)
{
	int i, alias_len;

	/* validate the arguments */
	if (alias_name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_len(alias_name);

	for (i = 0; data->alias_list[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_cmp(alias_name, data->alias_list[i], alias_len) &&
			data->alias_list[i][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[i] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, info *data)
{
	int i, j;
	char buffer[250] = {'0'}, *tmp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			tmp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_list[j]; j++)
		if (str_cmp(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[j]);
			break;
		}

	/* add the alias */
	if (tmp)
	{/* if the alias already exist */
		add_buffer(buffer, "=");
		add_buffer(buffer, tmp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
