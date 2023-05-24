#include "shell.h"
/**
 * exec_list- searches for match and execute the associate builtin.
 * @data : struct for programs data.
 * Return: the return of the function executed if there is a match.
 * -1 otherwise
 */
int exec_list(info *data)
{
	int i;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (str_cmp(options[i].builtin, data->cmd_name, 0))
			return (options[i].func(data));
	}
	return (-1);
}
