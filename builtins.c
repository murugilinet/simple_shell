#include "shell.h"

/**
 * builtin_exit - exit of the program with the status code
 * @data: struct for the program's data
 * Return: 0 if sucess, or other number if its declared in the arguments
 */
int builtin_exit(info *data)
{
	int i;

	if (data->token[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (i = 0; data->token[1][i]; i++)
			if ((data->token[1][i] < '0' || data->token[1][i] > '9')
				&& data->token[1][i] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->token[1]);
	}
	free_data(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: struct for the program's data
 * Return: 0 if sucess
 * or other number if its declared in the arguments
 */
int builtin_cd(info *data)
{
	char *home_dir = env_get_var("HOME", data), *old_dir = NULL;
	char dir_old[128] = {0};
	int error_code = 0;

	if (data->token[1])
	{
		if (str_cmp(data->token[1], "-", 0))
		{
			old_dir = env_get_var("OLDPWD", data);
			if (old_dir)
				error_code = set_work_dir(data, old_dir);
			_prints(env_get_var("PWD", data));
			_prints("\n");

			return (error_code);
		}
		else
		{
			return (set_work_dir(data, data->token[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(dir_old, 128);

		return (set_work_dir(data, home_dir));
	}
	return (0);
}

/**
 * set_work_dir - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_work_dir(info *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_cmp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_var("PWD", new_dir, data);
	}
	env_set_var("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(info *data)
{
	int i, len = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	/* validate args */
	if (data->token[1] == NULL)
	{
		_prints(messages[0] + 6);
		return (1);
	}
	if (data->token[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (i = 0; messages[i]; i++)
	{
		len = str_len(data->token[1]);
		if (str_cmp(data->token[1], messages[i], len))
		{
			_prints(messages[i] + len + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_alias(info *data)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (data->token[1] == NULL)
		return (print_alias(data, NULL));

	while (data->token[++i])
	{/* if there are arguments, set or print each env variable*/
		if (count_character(data->token[i], "="))
			set_alias(data->token[i], data);
		else
			print_alias(data, data->token[i]);
	}

	return (0);
}
