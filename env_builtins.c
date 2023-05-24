#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_env(info *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	/* if not arguments */
	if (data->token[1] == NULL)
		print_env(data);
	else
	{
		for (i = 0; data->token[1][i]; i++)
		{/* checks if exists a char = */
			if (data->token[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_duplicate(env_get_var(cpname, data));
				if (var_copy != NULL)
					env_set_var(cpname, data->token[1] + i + 1, data);

				/* print the environ */
				print_env(data);
				if (env_get_var(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_prints(data->token[1]);
					_prints("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_var(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->token[1][i];
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_set_env(info *data)
{
	/* validate args */
	if (data->token[1] == NULL || data->token[2] == NULL)
		return (0);
	if (data->token[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	env_set_var(data->token[1], data->token[2], data);

	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int builtin_unset_env(info *data)
{
	if (data->token[1] == NULL)
		return (0);
	if (data->token[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	env_remove_key(data->token[1], data);

	return (0);
}
