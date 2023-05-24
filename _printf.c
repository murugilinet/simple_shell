#include "shell.h"

/**
 * _prints- prints an array of char in STDOUT.
 * @str: pointer to array of chars.
 * Return: number of bytes writen
 * -1 on error and errno set appropriately.
 */
int _prints(char *str)
{
	return (write(STDOUT_FILENO, str, str_len(str)));
}

/**
 * print_err - prints an array of charaa in STDERR
 * @str: pointer to array of characters
 * Return: number of bytes written
 * -1 on error and set errno
 */
int print_err(char *str)
{
	return (write(STDERR_FILENO, str, str_len(str)));
}

/**
 * print_errcode- writes an array of chars in STDERR
 * @data: pointer to programs data
 * @errcode: error code to be printed
 * Return: number of bytes written
 * -1 on error snd set errno
 */
int print_errcode(int errcode, info *data)
{
	char  n_as_string[10] = {'\0'};

	num_to_string((long) data->exec_count, n_as_string, 10);

	if (errcode == 126)
	{
		print_err(data->prog_name);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->cmd_name);
		print_err(": Permission denied!\n");
	}
	else if (errcode == 127)
	{
		print_err(data->prog_name);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->cmd_name);
		print_err(": not found\n");
	}
	else if (errcode == 2 || errcode == 3)
	{
		print_err(data->prog_name);
		print_err(": ");
		print_err(n_as_string);
		print_err(": ");
		print_err(data->token[0]);
		if (errcode == 2)
			print_err(": number not allowed: ");
		else
			print_err(": cannot cd to ");
		print_err(data->token[1]);
		print_err("\n");
	}
	return (0);
}
