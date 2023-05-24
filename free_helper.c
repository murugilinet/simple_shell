#include "shell.h"
/**
 * free_recurrent- frees all recurrent data in loopa
 * @data: struct for programs data
 * Return: nothing
 */
void free_recurrent(info *data)
{
	if (data->token)
		free_arr_ptr(data->token);
	if (data->input)
		free(data->input);
	if (data->cmd_name)
		free(data->cmd_name);

	data->input = NULL;
	data->cmd_name = NULL;
	data->token = NULL;
}
/**
 * free_data - free all field of the data
 * @data: struct of the progrms data
 * Return: nothing
 */
void free_data(info *data)
{
	if (data->fd != 0)
	{
		if (close(data->fd))
			perror(data->prog_name);
	}
	free_recurrent(data);
	free_arr_ptr(data->env);
	free_arr_ptr(data->alias_list);
}
/**
 * free_arr_ptr- frees each pointer of an array of pointers
 * and the array too
 * @arr: array of ponters
 * Return: nothing
 */
void free_arr_ptr(char **arr)
{
	int i;

	if (arr != NULL)
	{
		for (i = 0; arr[i]; i++)
			free(arr[i]);

		free(arr);
		arr = NULL;
	}
}
