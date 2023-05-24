#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - finds a program in path.
 * @data: a pointer to the program's data.
 * Return: 0 if success, errcode otherwise.
 */

int find_program(info *data)
{
	int i = 0, ret_code = 0;
	char **dirs;

	if (!data->cmd_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (check_file(data->cmd_name));

	free(data->token[0]);
	data->token[0] = str_cat(str_duplicate("/"), data->cmd_name);
	if (!data->token[0])
		return (2);

	dirs = tokenize_path(data);/* search in the PATH */

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{/* appends the function_name to path */
		dirs[i] = str_cat(dirs[i], data->token[0]);
		ret_code = check_file(dirs[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->token[0]);
			data->token[0] = str_duplicate(dirs[i]);
			free_arr_ptr(dirs);
			return (ret_code);
		}
	}
	free(data->token[0]);
	data->token[0] = NULL;
	free_arr_ptr(dirs);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(info *data)
{
	int i = 0;
	int count_dirs = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_var("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of directories in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirs++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * count_dirs);

	/*tokenize and duplicate each token of path*/
	i = 0;
	tokens[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exio "/bin/ls" | ./hsht the file*/
	errno = 127;
	return (127);
}
