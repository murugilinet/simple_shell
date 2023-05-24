#include "shell.h"

/**
 * env_get_var - gets the value of an environment variable.
 * @var: the environment variable of interest.
 * @data: struct of the program's data.
 * Return: a pointer to the value of the variable.
 * NULL if it doesn't exist
 */
char *env_get_var(char *var, info *data)
{
	int i, var_length = 0;

	if (var == NULL || data->env == NULL)
		return (NULL);

	var_length = str_len(var);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the name */
		if (str_cmp(var, data->env[i], var_length) &&
		 data->env[i][var_length] == '=')
		{
			return (data->env[i] + var_length + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_var - overwrite the value of the environment variable
 * or create it if does not exist.
 * @var: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_var(char *var, char *value, info *data)
{
	int i, var_length = 0, new_var = 1;

	if (var == NULL || value == NULL || data->env == NULL)
		return (1);

	var_length = str_len(var);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_cmp(var, data->env[i], var_length) &&
		 data->env[i][var_length] == '=')
		{/* If key already exists */
			new_var = 0;
			/* free the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[i] = str_cat(str_duplicate(var), "=");
	data->env[i] = str_cat(data->env[i], value);

	if (new_var)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, info *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_len(key);

	for (i = 0; data->env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_cmp(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* if key already exists, remove them */
			free(data->env[i]);

			/* move the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_env- prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_env(info *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_prints(data->env[j]);
		_prints("\n");
	}
}
